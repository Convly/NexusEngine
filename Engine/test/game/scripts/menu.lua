function Init()
end

function displayAlertConnectionToServer()
    ip = Env:getSceneByName("Menu"):getLayerByName("Home"):getTextInputByName("IpAddressTextInput"):getGuiTextInputInfos():getTextInfo():getTextLabel()
    port = Env:getSceneByName("Menu"):getLayerByName("Home"):getTextInputByName("PortTextInput"):getGuiTextInputInfos():getTextInfo():getTextLabel()
    print("ip:" .. ip .. " port:" .. port)
    Conn.localConnect("127.0.0.1", 9898)
end