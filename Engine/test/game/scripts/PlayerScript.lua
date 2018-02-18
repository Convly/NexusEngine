function Init()
    print("Init for playerscript.lua")
end

function UpdatePlayer(player, keyboard)
    dirX = 0.0
    dirY = 0.0

    if keyboard:getKeyState(71) then
        dirX = -0.03
    end
    if keyboard:getKeyState(72) then
        dirX = 0.03
    end
    if keyboard:getKeyState(73) then
        dirY = -0.03
    end
    if keyboard:getKeyState(74) then
        dirY = 0.03
    end    
    player:getTransformComponent():getDirection():setVX(dirX)
    player:getTransformComponent():getDirection():setVY(dirY)

    print(player:getEntityInfos():getName() .. " x=" .. player:getTransformComponent():getPos().x)
    print(player:getEntityInfos():getName() .. " y=" .. player:getTransformComponent():getPos().y)
end

function UpdatePlayerMove()
    nbClient = Env:getConnectedClient()

    if nbClient >= 1 then
        UpdatePlayer(Env:getSceneByName("Game"):getGameObjectByName("Player1"), Env:getKeyboardAt(0))
    end
    if nbClient >= 2 then
        UpdatePlayer(Env:getSceneByName("Game"):getGameObjectByName("Player2"), Env:getKeyboardAt(1))
    end
    if nbClient >= 3 then
        UpdatePlayer(Env:getSceneByName("Game"):getGameObjectByName("Player3"), Env:getKeyboardAt(2))
    end
    if nbClient >= 4 then
        UpdatePlayer(Env:getSceneByName("Game"):getGameObjectByName("Player4"), Env:getKeyboardAt(3))
    end
end

function Update()
    -- if Env:getConnectedClient() > 0 then
    --     print(Env:getKeyboardAt(0):getKeyState(73))
    --     -- Env:getKeyboardAt(0):print()
    -- end
    UpdatePlayerMove()
end

function NewClientConnected()
    print("A client has been connected to the server!")
end

function FixedUpdate()

end

function LateUpdate()

end