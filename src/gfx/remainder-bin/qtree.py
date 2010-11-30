import sys, random, time
from random import randint

# -----------------------------------------------------------------------------
class Error(object):
    def __init__(self):
        self.msg_stack = []
        self.ok = self.__class__.__name__ + "-OK"
        self.cur = self.ok       
        self.alerts = "on"

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

    def AlertsOff(self):
        self.alerts = "off"

    def AlertsOn(self):
        self.alerts = "on"

    def Alert(self, msg):
        if self.alerts == "on":
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

    @staticmethod
    def random_el(lim):
        return Point(randint(-lim, lim), randint(-lim, lim))

    def __repr__(self):
        return str( (self.x, self.y) )

    def north_of(self, p): return self.y < p.y # 
    def south_of(self, p): return self.y > p.y
    def east_of(self, p): return self.x > p.x
    def west_of(self, p): return self.x < p.x
        
    def northwest_of(self,p): return self.north_of(p) and self.west_of(p)
    def northeast_of(self,p): return self.north_of(p) and self.east_of(p)
    def southwest_of(self,p): return self.south_of(p) and self.west_of(p)
    def southeast_of(self,p): return self.south_of(p) and self.east_of(p)

# -----------------------------------------------------------------------------
IN_BOUNDS, OUT_OF_BOUNDS, NE, NW, SW, SE = -2, -1, 0, 1, 2, 3

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
        self.AlertsOff()
        
    # boolean 
    def is_inited(self): return self._inited

    def empty(self):
        return self.nodes == [None, None, None, None]
                 
    def set_box(self, ul, br):
        self.upperleft = ul
        self.bottomright = br

    def box_area(self):
        return ( (self.bottomright.x - self.upperleft.x) * 
                 (self.bottomright.y - self.upperleft.y) )

    def size(self):
        if self.upperleft == None:
            self.SetReportErr("upperleft is None when trying to width()")
        if self.bottomright == None:
            self.SetReportErr("bottomright is None when trying to width()")
        result = self.bottomright.x - self.upperleft.x
        if result < 0:
            self.SetReportErr("size() trying to return a negative width")
        return result

    def is_leaf(self):
        return self.size() == self.resolution
    
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
                                     
    def insert(self, p):             
        #self.Alert("inserting " + str(p))
        quad = self.which_quadrant(p)
        if self.is_leaf():
            #self.Alert("storing point " + str(p))
            self.points.append(p)

        else:
            node = self.nodes[quad]
            qt = QuadTree(self.resolution)
            qt._inited = True # users don't worry about this.
            qt.upperleft = Point(self.upperleft.x,self.upperleft.y)
            qt.bottomright = Point(self.bottomright.x,self.bottomright.y)

            if node == None:
                half = self.size()/2
                if quad == NE:
                    qt.upperleft.move_east(half)
                    qt.bottomright.move_north(half)
                if quad == NW:
                    qt.bottomright.move_north(half)
                    qt.bottomright.move_west(half)
                if quad == SW:
                    qt.upperleft.move_south(half)
                    qt.bottomright.move_west(half)
                if quad == SE:
                    qt.upperleft.move_south(half)
                    qt.upperleft.move_east(half)
                    
                self.nodes[quad] = qt
            self.nodes[quad].insert(p)

class QTree(Error): # this is a wrapper manager for QuadTree.
    '''
    QuadTree is unbounded so the root needs to swap when an
    out of bounds element is inserted.
    '''
    def __init__(self, resolution):
        Error.__init__(self)
        self.root = QuadTree(resolution)

    def out_where(self, p):
        ul = self.root.upperleft
        br = self.root.bottomright

        if p.northeast_of( Point(ul.x, br.y) ): return NE
        if p.northwest_of( Point(br.x, br.y) ): return NW
        if p.southeast_of( Point(ul.x, ul.y) ): return SE
        if p.southwest_of( Point(br.x, ul.y) ): return SW

        return IN_BOUNDS # oops.

    def grow(self, p, way):        
        qt = QuadTree(self.root.resolution)            
        qt.upperleft = Point(self.root.upperleft.x, self.root.upperleft.y)
        qt.bottomright = Point(self.root.bottomright.x, self.root.bottomright.y)            
        qt._inited = True

        # Double boundary in the <way> direction.
        self.Alert("Growing\nfrom: " + str((qt.upperleft, qt.bottomright, qt.box_area())))
        if way == NE:
            qt.upperleft.move_north(self.root.size())
            qt.bottomright.move_east(self.root.size())
        
        if way == NW:
            qt.upperleft.move_north(self.root.size())
            qt.upperleft.move_west(self.root.size())
    
        if way == SW:
            qt.bottomright.move_south(self.root.size())
            qt.upperleft.move_west(self.root.size())
        
        if way == SE:
            qt.bottomright.move_east(self.root.size())
            qt.bottomright.move_south(self.root.size())

        self.Alert("to: " + str((qt.upperleft, qt.bottomright, qt.box_area())))
        self.Alert("")

        opposite_way = (way + 2) % 4

        qt.nodes[opposite_way] = self.root        
        self.root = qt        

        # coninue to grow in the <way> direction
        if self.root.which_quadrant(p) == OUT_OF_BOUNDS:
            self.grow(p, way)
    
    def insert(self, p):
        if not self.root._inited:
            self.root.insert_first(p)

        quad = self.which_quadrant(p)
        if quad == OUT_OF_BOUNDS:
            way = self.out_where(p)

            if way == NE:                
                self.grow(p, NE)
            elif way == NW:
                self.grow(p, NW)
            elif way == SW:
                self.grow(p, SW)
            elif way == SE:
                self.grow(p, SE)
            else:
                SetReportErr('''
Undefined behavior: Qtree.insert. Bounds 
the point comparison is to blame because it uses bare >, <
when half of them should be >=, <=.  Need to figure out
which ones are which.
''')
        self.root.insert(p)

    def in_box(self, p): 
        return self.root.in_box(p)

    def which_quadrant(self, p): 
        return self.root.which_quadrant(p)
   

def main():
    res = 16
    qt = QTree(res)
    p = Point(0, 0)
    qt.insert(p)

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

    tp = Point(0,0)
    tp.move_east(1)
    print tp.x == 1
    print tp.y == 0
    
    tp = Point(0,0)
    tp.move_west(1)
    print tp.x == -1
    print tp.y == 0

    tp = Point(0,0)
    tp.move_north(1)
    print tp.x == 0
    print tp.y == -1

    tp = Point(0,0)
    tp.move_south(1)
    print tp.x == 0
    print tp.y == 1

    tp = Point(0,0)
    ne = Point(1, -1)
    nw = Point(-1, -1)
    sw = Point(-1, 1)
    se = Point(1,1)

    print ne.north_of(tp)
    print ne.east_of(tp)
    print nw.west_of(tp)
    print nw.north_of(tp)
    print sw.west_of(tp)
    print sw.south_of(tp)
    print se.east_of(tp)
    print se.south_of(tp)

    print ne.northeast_of(tp)
    print nw.northwest_of(tp)
    print se.southeast_of(tp)
    print sw.southwest_of(tp)

    pts = [Point.random_el(1000) for x in range(1000)]

    print "inserting"
    start = time.time()
    for p in pts:
        qt.insert(p)
    stop = time.time()
    print stop-start
        
if __name__ == "__main__":

    import hotshot
    prof = hotshot.Profile("hotshot_edi_stats")
    prof.runcall(main)
    prof.close()

    from hotshot import stats
    s = stats.load("hotshot_edi_stats")
    s.sort_stats("time").print_stats()

