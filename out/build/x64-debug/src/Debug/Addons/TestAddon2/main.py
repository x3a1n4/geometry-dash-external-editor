import gdee

print("Number of arguments", gdee.numargs())

def register():
    print("Registered TestAddon2")
    gdee.print("Hello from TestAddon2!")
    
def unregister():
    print("Unregistered TestAddon2")