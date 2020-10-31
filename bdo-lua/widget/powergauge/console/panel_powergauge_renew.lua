Panel_PowerGauge:SetShow(false)
local progress = UI.getChildControl(Panel_PowerGauge, "Progress2_Gauge")
local progressValue = UI.getChildControl(Panel_PowerGauge, "StaticText_GaugeValue")
local readyText = UI.getChildControl(Panel_PowerGauge, "StaticText_Ready")
local wp = 0
local checkValue = false
local elapsTime = 0
function PowerGauge_FrameUpdate(deltaTime)
  elapsTime = elapsTime + deltaTime
  if checkValue then
    local nowPower = ToClient_getCommonGauge()
    local maxPower = ToClient_getMaxCommonGauge()
    local percent = nowPower / maxPower * 100
    if wp < math.floor(nowPower) or math.floor(nowPower) > 10 and math.floor(nowPower) < 0 then
      return
    end
    readyText:SetShow(false)
    progressValue:SetShow(true)
    progressValue:SetText(math.floor(nowPower))
    progress:SetProgressRate(percent)
    progress:SetCurrentProgressRate(percent)
  else
    readyText:SetShow(true)
    progressValue:SetShow(false)
    readyText:SetText(PAGetString(Defines.StringSheet_GAME, "LUA_POWERGAUGE_READY"))
  end
end
local resetCheck = false
function FGlobal_PowerGauge_Open()
  checkValue = false
  if not resetCheck then
    resetCheck = true
    elapsTime = 0
    progress:SetProgressRate(0)
    progress:SetCurrentProgressRate(0)
  end
  FromClient_PowerGauge_onScreenResize()
  Panel_PowerGauge:SetShow(true)
  local selfPlayer = getSelfPlayer()
  if nil == selfPlayer then
    return
  end
  wp = selfPlayer:getWp()
  if 0 == wp then
    Proc_ShowMessage_Ack(PAGetString(Defines.StringSheet_GAME, "LUA_POWERGAUGE_NOPOWER"))
  end
end
function FGlobal_PowerGuage_StatCheck()
  checkValue = true
  resetCheck = false
end
function FGlobal_PowerGauge_Close()
  Panel_PowerGauge:SetShow(false)
end
function FromClient_PowerGauge_onScreenResize()
  Panel_PowerGauge:SetPosX(getOriginScreenSizeX() / 2 - Panel_PowerGauge:GetSizeX() * 3 - 100)
  Panel_PowerGauge:SetPosY(getOriginScreenSizeY() / 2 - 200)
end
registerEvent("onScreenResize", "FromClient_PowerGauge_onScreenResize")
Panel_PowerGauge:RegisterUpdateFunc("PowerGauge_FrameUpdate")
