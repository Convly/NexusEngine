function Init()
    Conn.localConnect("127.0.0.1", 9898)
end

function displayAlertConnectionToServer()
    Env:getSceneAt(0):getLayerAt(0):getTextAt(0):getGuiTextInfos():getTextInfo():setFontSize(30)
end