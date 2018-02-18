function Init()
    print("Init for playerscript.lua")
end

function Update()
    if Env:getConnectedClient() > 0 then
        print(Env:getKeyboardAt(0):getKeyState(73))
        -- Env:getKeyboardAt(0):print()
    end
end

function NewClientConnected()
    print("A client has been connected to the server!")
end

function FixedUpdate()

end

function LateUpdate()

end