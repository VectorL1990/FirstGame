
local LuaTestCase=import('LuaTestCase');
local KismetStringLibrary = import('KismetStringLibrary');
local KismetSystemLibrary = import('KismetSystemLibrary');
local GameplayStatics = import("GameplayStatics")
local stringType = UEnums.EPropertyClass.Str
local LuaTestCaseInstance = LuaTestCase();


--功能函数---------------------------------------------------

--所有回调函数------------------------------------------------------

function LuaInputTextCommitCallback(text, textFunction)
    local loginGameMode = LuaTestCaseInstance:GetLoginGameMode()
    if textFunction == "TextInput_Account" then
        loginGameMode.m_loginAccountName = text
    elseif textFunction == "TextInput_Code" then
        loginGameMode.m_loginCode = text
    end
end


function LuaButtonClickCallback(buttonFunction)
    if buttonFunction == "Button_Login" then
        --[[local clientDataArray = slua.Array(stringType)
        local stringArray = KismetStringLibrary.GetCharacterArrayFromString("CollisionWar")
        for i, s in pairs(stringArray) do
            clientDataArray:Add(s)
        end]]
        local loginGameMode = LuaTestCaseInstance:GetLoginGameMode()
        if loginGameMode.m_loginAccountName == "" then
            return
        end
        if loginGameMode.m_loginCode == "" then
            return
        end
        local loginPlayerController = LuaTestCaseInstance:GetLoginPlayerController()
        loginPlayerController:ButtonLoginClickCallback("CollisionWar", loginGameMode.m_loginAccountName, loginGameMode.m_loginCode)
        loginPlayerController:LoadLoadMenu()
        --进行账号名称判断，如名称长度为0，拒绝登录申请
        --进行密码判断，如密码长度为0，拒绝登录申请
    elseif buttonFunction == "Button_CreateAccount" then
        local loginGameMode = LuaTestCaseInstance:GetLoginGameMode()
        if loginGameMode.m_loginAccountName == "" then
            return
        end
        if loginGameMode.m_loginCode == "" then
            return
        end
        local loginPlayerController = LuaTestCaseInstance:GetLoginPlayerController()
        print(loginGameMode.m_loginAccountName)
        print(loginGameMode.m_loginCode)
        loginPlayerController:ButtonCreateAccountClickCallback("CollisionWar", loginGameMode.m_loginAccountName, loginGameMode.m_loginCode)
    elseif buttonFunction == "Button_Exit" then
        local loginGameMode = LuaTestCaseInstance:GetLoginGameMode()
        loginGameMode.m_isExitGame = true
        loginGameMode.m_tickFlag = false
        local loginPlayerController = LuaTestCaseInstance:GetLoginPlayerController()
        loginPlayerController.m_pLoginMenu:AskMenuFadeOut()
    end
end

function LuaMenuFadeOutDoneCallback(menuName)
    if menuName == "LoginMenu" then
        local loginPlayerController = LuaTestCaseInstance:GetLoginPlayerController()
        local CWGameMode = LuaTestCaseInstance:GetCWGameMode()
        loginPlayerController.m_pLoginMenu:RemoveFromParent()
        CWGameMode:QuitGame()
    end
end


function LuaDealNewMessage(message)
    local loginGameMode = LuaTestCaseInstance:GetLoginGameMode()
    local loginPlayerController = LuaTestCaseInstance:GetLoginPlayerController()
    if message == "dispatchPlayerInfo" then
        print("Login::LuaDealNewMessage dispatchPlayerInfo")
        loginPlayerController:SetLoadMenuProgressSliderPercentage(loginGameMode.m_loginProgress + 50)
        loginGameMode.m_loginProgress = loginGameMode.m_loginProgress + 50
    elseif message == "dispatchMallInfoList" then
        print("Login::LuaDealNewMessage dispatchMallInfoList")
        loginPlayerController:SetLoadMenuProgressSliderPercentage(loginGameMode.m_loginProgress + 50)
        loginGameMode.m_loginProgress = loginGameMode.m_loginProgress + 50
    elseif message == "dispatchRelogonInfo" then
        loginPlayerController:SetLoadMenuProgressSliderPercentage(loginGameMode.m_loginProgress + 50)
        loginGameMode.m_loginProgress = loginGameMode.m_loginProgress + 50
    elseif message == "dispatchMatchResult" then
        loginPlayerController:SetLoadMenuProgressSliderPercentage(loginGameMode.m_loginProgress + 20)
        loginGameMode.m_loginProgress = loginGameMode.m_loginProgress + 20
    elseif message == "dispatchRelogonPlayerInfo" then
        loginPlayerController:SetLoadMenuProgressSliderPercentage(loginGameMode.m_loginProgress + 40)
        loginGameMode.m_loginProgress = loginGameMode.m_loginProgress + 40
    elseif message == "dispatchAllPlayerRoletypeAndAssignNb" then
        loginPlayerController:SetLoadMenuProgressSliderPercentage(loginGameMode.m_loginProgress + 30)
        loginGameMode.m_loginProgress = loginGameMode.m_loginProgress + 30
    elseif message == "PlayerEnterWorld" then
        loginPlayerController:SetLoadMenuProgressSliderPercentage(loginGameMode.m_loginProgress + 10)
        loginGameMode.m_loginProgress = loginGameMode.m_loginProgress + 10
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        gameInstance.m_isNormalEnterBattle = false
        gameInstance.m_hasCSEnterWorld = true
    end
end




--[[
print("hello world")


xx={}
function xx.text(v)
    print("xx.text",v)
end

function bpcall(a,b,c,d)
    --print("call from bp",a,b,c,d)
    return 1024,"return from lua 虚幻引擎"
end

local HitResult = import('HitResult');
local tt=0
local ret={1,2,3,4,5}
function update(dt,actor)
    tt=tt+dt
    local p = actor:K2_GetActorLocation()
    local h = HitResult()
    local v = FVector(math.sin(tt)*100,2,3)
    local offset = FVector(0,math.cos(tt)*50,0)
    local ok,h=actor:K2_SetActorLocation(v+offset,true,h,true)

    collectgarbage("collect")
    return 1024,2,"s",ret,function() end
end

function implementSkill(skillName, actor)
    if skillName == "kouxue"
    then
        local actorLoc = actor:K2_GetActorLocation()
        local offset = FVector(100,0,0)
        actorLoc = offset + actorLoc
        local h = HitResult()
        actor:K2_SetActorLocation(actorLoc, true, h, true)
    end
    print("slua::implementSkill slua has implement skill")
end

function setPCTestVal(pc)
    print("slua::setPCTestVal slua has change m_luaTestVal")
    pc.m_luaTestVal = pc.m_luaTestVal+1
end

return 1024

]]