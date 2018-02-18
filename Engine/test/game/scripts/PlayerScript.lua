
function Init()
    print("Init for playerscript.lua")
end

function Update()
    Env:getSceneAt(0):getLayerAt(0):getTextAt(0):getGuiTextInfos():getTextInfo():setFontSize(100)
    print("Update for playerscript.lua")
end

function FixedUpdate()

end

function LateUpdate()

end