class Class(object):
    def __init__(self):
        self.inherits = set()
        self.composes = set()
    
    def inherit(self, *names):
        for n in names:
            self.inherits.add(n)

    def compose(self, name):
        for n in names:
            self.composes.add(n)
    
class Package(object):
    def __init__(self):
        self.classes = set()


if __name__ == "__main__":
    core = Package()

    Error = Class()



    gfx_classes = [ Mover, Vector, Text, Drawer, 
                    Layer, Font, Color] = [Class() for x in range(7)]
        
    Text.inherit(Mover, Drawer)
    Layer.inherit(Mover)
    Font.inherit(Error)

    gfx = Package()
    

