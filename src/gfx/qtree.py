import sys
from random import randint

# -----------------------------------------------------------------------------
class Error(object):
    def __init__(self):
        self.msg_stack = []
        self.ok = self.__class__.__name__ + "-OK"
        self.cur = self.ok       

    def Ok(self):
        return self.cur == self.ok
    
    def ErrMsg(self):
        return self.cur

    def Err(self, msg):
        self.cur = msg
        self.msg_stack.append(msg)

    def Show(self, msg):
        print "]", self.__class__.__name__, "<--", msg

    def ReportAllDie(self):
        for msg in self.msg_stack:
            self.Show(msg)
        self.Alert("\n\n")
        sys.exit()

    def SetReportErr(self, msg):
        self.Err(msg)
        self.ReportErr()

    def ReportErr(self):
        self.Show(self.cur)

    def Alert(self, msg):
        sys.stdout.write(msg + "\n")


# -----------------------------------------------------------------------------
class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def move_east(self, n): self.x += n
    def move_west(self, n): self.x -= n
    def move_north(self, n): self.y -= n
    def move_south(self, n): self.y += n
        
    def __repr__(self):
        return str( (self.x, self.y) )


# -----------------------------------------------------------------------------
OUT_OF_BOUNDS, NE, NW, SW, SE = -1, 0, 1, 2, 3

class QuadTree(Error):
    def __init__(self, resolution):              
        Error.__init__(self)
        self.resolution = resolution
        self._inited = False
        self.points = []        
        self.upperleft = None
        self.bottomright = None
        self.parent = None
        self.nodes = [None, None, None, None]

    # boolean 
    def is_inited(self): return self._inited

    def empty(self):
        return self.nodes == [None, None, None, None]
                 
    def set_box(self, ul, br):
        self.upperleft = ul
        self.bottomright = br

    def size(self):
        if self.upperleft == None:
            self.SetReportErr("upperleft is None when trying to width()")
        if self.bottomright == None:
            self.SetReportErr("bottomright is None when trying to width()")
        result = self.bottomright.x - self.upperleft.x
        if result < 0:
            self.SetReportErr("size() trying to return a negative width")
        return result
    
    def in_north(self, p):
        return ( p.y >= self.upperleft.y and 
                 p.y < self.upperleft.y + self.size()/2 )

    def in_south(self, p):
        return ( p.y < self.bottomright.y and
                 p.y >= self.upperleft.y + self.size()/2 )

    def in_east(self, p):
        return ( p.x >= self.upperleft.x + self.size()/2 and 
                 p.x < self.bottomright.x )
                
    def in_west(self, p):
        return ( p.x < self.upperleft.x + self.size()/2 and
                 p.x >= self.upperleft.x )
               
    def which_quadrant(self, p):
        if self.in_north(p) and self.in_east(p):
            return NE
        if self.in_north(p) and self.in_west(p):
            return NW
        if self.in_south(p) and self.in_east(p):
            return SE
        if self.in_south(p) and self.in_west(p):
            return SW
        return OUT_OF_BOUNDS

    def in_box(self, p):
        '''
        box includes the left and top edges, excludes
        bottom and right edges to maintain sanity.
        '''       
        if not self._inited:
            self.SetReportErr("Tree is not initialized.")
            self.ReportAllDie()
        
        return ( p.x >= self.upperleft.x and
                 p.x < self.bottomright.x and
                 p.y >= self.upperleft.y and
                 p.y < self.bottomright.y )
                 
    def insert_first(self, p):             
        if self._inited:
            self.SetReportErr("Trying to insert_first into an old tree, should be using `insert`")
            self.ReportAllDie()

        # mods align tree to imaginary grid.
        ul = Point(p.x - (p.x % self.resolution), p.y - (p.y % self.resolution))
        br = Point(ul.x + self.resolution, ul.y + self.resolution)
        self.points.append(p)
        self.upperleft = ul
        self.bottomright = br
        self._inited = True
   
    def out_west(self, p): return p.x < self.upperleft.x
    def out_east(self, p): return p.x >= self.bottomright.x
    def out_north(self, p): return p.y < self.upperleft.y
    def out_south(self, p): return p.y >= self.bottomright.y

    def grow(self, p, way):
        print "Growing", way
        qt = QuadTree(self.resolution)            
        qt.upperleft = Point(self.upperleft.x, self.upperleft.y)
        qt.bottomright = Point(self.bottomright.x, self.bottomright.y)            

        # Double boundary in the right direction.
        if way == NE:
            qt.upperleft.move_north(self.size())
            qt.bottomright.move_east(self.size())
        
        if way == NW:
            qt.upperleft.move_north(self.size())
            qt.upperleft.move_west(self.size())
    
        if way == SW:
            qt.upperleft.move_west(self.size())
            qt.bottomright.move_south(self.size())
        
        if way == SE:
            qt.bottomright.move_east(self.size())
            qt.bottomright.move_south(self.size())

        # 
        # SLEEP ON THIS.
        # Because this could be seriously incorrect.

        opposite_way = (way + 2) % 4
        qt.nodes[opposite_way] = self
        self.parent = qt
        qt.parent = None
        self = qt

        if self.which_quadrant(p) == OUT_OF_BOUNDS:
            self.grow(p, way) # reuse this way. 
        
                           
    def insert(self, p):        
        quad = self.which_quadrant(p)
        if quad == OUT_OF_BOUNDS:
            if self.out_north(p) and self.out_east(p):
                self.grow(p, NE)
            if self.out_north(p) and self.out_west(p):
                self.grow(p, NW)
            if self.out_south(p) and self.out_west(p):
                self.grow(p, SW)
            if self.out_south(p) and self.out_east(p):
                self.grow(p, SE)
            
            '''
            make a new tree with a boundary twice the width
            of this one.
            plug this tree into one of it's nodes.
            switch the root to the bigger tree.

            '''
        #elif self.is_leaf():
        #    self.store(p, quad)
        #else:
        #    self.insert(p, quad)


if __name__ == "__main__":
    res = 16
    qt = QuadTree(res)
    p = Point(0, 0)
    qt.insert_first(p)

    # literal edge and corner cases.
    p1 = Point(0, 0)
    print qt.in_box(p1) == True
    print qt.which_quadrant(p1) == NW
    
    p2 = Point(res,res)
    print qt.in_box(p2) == False

    p3 = Point(res/2, res/2)
    print qt.in_box(p3) == True
    print qt.which_quadrant(p3) == SE

    p4 = Point(res/2-1, res/2)
    print qt.in_box(p4) == True
    print qt.which_quadrant(p4) == SW

    p5 = Point(res/2-1, res/2-1)
    print qt.in_box(p5) == True
    print qt.which_quadrant(p5) == NW

    p6 = Point(res/2-1, res/2-1)
    print qt.in_box(p6) == True
    print qt.which_quadrant(p6) == NW

    p7 = Point(res, 0)
    print qt.in_box(p7) == False

    p8 = Point(0, res)
    print qt.in_box(p8) == False


    def opp(w):
        return (w + 2)%4
    
    print opp(NE) == SW
    print opp(NW) == SE
    print opp(SW) == NE
    print opp(SE) == NW
    
    qt.insert(p2)
    qt.insert(p8)
    qt.insert(p7)
    qt.insert(p6)

    
