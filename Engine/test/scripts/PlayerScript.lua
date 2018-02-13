function Init()
    print("Init for playerscript.lua")
    scriptPath = Env:getRessources():getScriptPathAt(0)
    print(scriptPath)
    print("ALLLLLLLLLLLLLLLLLLL")
    x = 1
end

function Update()
    print("Update for playerscript.lua", x)
    x = x + 1
end

function FixedUpdate()
    print("Fixedupdate for playerscript.lua", x) 
    x = x - 1
end

function LateUpdate()
    print("LateUpdate for playerscript.lua", x)
    x = x + 2
end