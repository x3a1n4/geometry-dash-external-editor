import gdee

print("Number of arguments", gdee.numargs())

def register():
    print("Registered TestAddon1")
    print("Number of arguments", gdee.numargs())
    gdee.print("Hello from TestAddon1!")
    
def unregister():
    print("Unregistered TestAddon1")