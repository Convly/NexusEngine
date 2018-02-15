
function Init()
    i = 0
    print("Init for playerscript.lua")
    scriptPath = Env:getRessources():getScriptPathAt(0)
    print(scriptPath)
end

function Update()
    i = (i + 1) % 10
    if i % 10 == 0 then
        Env:getSceneAt(0):getLayerAt(0):getTextAt(0):getGuiTextInfos():getTextInfo():setFontPath("on est 52")
    end
    print("Update for playerscript.lua")
end