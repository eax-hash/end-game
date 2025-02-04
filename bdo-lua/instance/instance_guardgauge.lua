local UI_color = Defines.Color
Instance_GuardGauge:SetShow(false, false)
local guardGauge = UI.getChildControl(Instance_GuardGauge, "Progress2_1")
local bar_FullGauge = UI.getChildControl(Instance_GuardGauge, "GuardGauge_ProgresssBG")
local txt_GuardGaugeMax = UI.getChildControl(Instance_GuardGauge, "StaticText_GuardGaugeCount")
Instance_GuardGauge:RegisterShowEventFunc(false, "Panel_GuardGauge_HideAni()")
function Panel_GuardGauge_HideAni()
  local aniInfo = UIAni.AlphaAnimation(0, Instance_GuardGauge, 0, 0.3)
  aniInfo:SetHideAtEnd(true)
end
local SpUseType = {
  Once = 0,
  Continue = 1,
  Recover = 2,
  Stop = 3,
  Reset = 4,
  None = 5
}
function GuardGauge_Update()
  local selfPlayerWrapper = getSelfPlayer()
  if nil ~= selfPlayerWrapper then
    local sp = selfPlayerWrapper:get():getCurrentGuard()
    local maxSp = selfPlayerWrapper:get():getMaxGuard()
    if sp == maxSp then
      bar_FullGauge:SetShow(true)
      bar_FullGauge:EraseAllEffect()
      Instance_GuardGauge:SetShow(false, false)
      return
    end
    if true == UI.isFlushedUI() then
      Instance_GuardGauge:SetShow(false, false)
      return
    end
    local spRate = sp / maxSp
    local alpha = (1 - spRate) * 15
    local fullGauge = spRate * 100
    if 1 < alpha then
      alpha = 1
    end
    Instance_GuardGauge:SetAlphaChild(alpha)
    guardGauge:SetProgressRate(fullGauge)
    txt_GuardGaugeMax:SetFontAlpha(alpha)
    txt_GuardGaugeMax:SetText(tostring(math.floor(spRate * 100)))
    Instance_GuardGauge:SetShow(true)
  end
end
registerEvent("FromClientGuardUpdate", "GuardGauge_Update()")
Instance_GuardGauge:RegisterUpdateFunc("GuardGauge_Update")
