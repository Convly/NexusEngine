local scores = {0, 0, 0, 0}
function Init()
    print("Init for playerscript.lua")
end

function UpdatePlayer(name, keyboard, id)
    dirX = 0.0
    dirY = 0.0

    if keyboard:getKeyState(71) then
        dirX = -3
    end
    if keyboard:getKeyState(72) then
        dirX = 3
    end
    if keyboard:getKeyState(73) then
        dirY = -3
    end
    if keyboard:getKeyState(74) then
        dirY = 3
    end    
    Env:getSceneByName("Game"):getGameObjectByName(name):getTransformComponent():getDirection():setVX(dirX)
    Env:getSceneByName("Game"):getGameObjectByName(name):getTransformComponent():getDirection():setVY(dirY)
    scores[id] = scores[id] + 1
    scoreName = "Player" .. tostring((id)) .. "ScoreValue"
    Env:getSceneByName("Game"):getLayerByName("HUD"):getTextByName(scoreName):getGuiTextInfos():getTextInfo():setTextLabel(tostring(scores[id]))
    

    -- print(Env:getSceneByName("Game"):getGameObjectByName(name):getEntityInfos():getName() .. " x=" .. Env:getSceneByName("Game"):getGameObjectByName(name):getTransformComponent():getPos().x)
    -- print(Env:getSceneByName("Game"):getGameObjectByName(name):getEntityInfos():getName() .. " y=" .. Env:getSceneByName("Game"):getGameObjectByName(name):getTransformComponent():getPos().y)
end

function UpdatePlayerMove()
    nbClient = Env:getConnectedClient()

    if nbClient >= 1 then
        UpdatePlayer("Player1", Env:getKeyboardAt(0), 1)
    end
    if nbClient >= 2 then
        UpdatePlayer("Player2", Env:getKeyboardAt(1), 2)
    end
    if nbClient >= 3 then
        UpdatePlayer("Player3", Env:getKeyboardAt(2), 3)
    end
    if nbClient >= 4 then
        UpdatePlayer("Player4", Env:getKeyboardAt(3), 4)
    end
end

function Update()
    UpdatePlayerMove()
end

function NewClientConnected()
    print("A client has been connected to the server!")
end

function FixedUpdate()

end

function LateUpdate()

end