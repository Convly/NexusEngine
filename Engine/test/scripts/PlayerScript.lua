print("Yolo")
Conn.localConnect("127.0.0.1", 9898)
print("Ahyola")

function Init()
    print("Init for playerscript.lua")
    scriptPath = Env:getRessources():getScriptPathAt(0)
    print(scriptPath)
end

function Update()
    print("Update for playerscript.lua")
end