function Init()
    Conn.localConnect("127.0.0.1", 9898)
end

function displayAlertConnectionToServer()
    Env:addScene("lol")
    color = RGBa(1, 2, 3, 4)
    txtInfo = TextInfo("pupupupute", "caca", 42, color, 1)
    gtxtInfo = GUITextInfos(txtInfo)
    txt = Text(GUIElementInfos(4), gtxtInfo)
    lay = Layer("lays")
    lay:addText(txt)
    Env:getSceneAt(0):addLayer(lay)
    print(Env:getSceneAt(0):getLayerAt(0):getTextAt(0):getGuiTextInfos():getTextInfo():getFontPath())
    Env:getSceneAt(0):getLayerAt(0):getTextAt(0):getGuiTextInfos():getTextInfo():setFontPath("on est 42")
    print(Env:getSceneAt(0):getLayerAt(0):getTextAt(0):getGuiTextInfos():getTextInfo():getFontPath())
    print(Env:getSceneAt(0))
    Conn.localDisconnect();
end