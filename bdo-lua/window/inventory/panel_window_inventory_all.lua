PaGlobal_Inventory_All = {
  _ui = {
    stc_titleBG = nil,
    check_popup = nil,
    btn_question = nil,
    btn_close = nil,
    stc_radioButtonBG = nil,
    rdo_normalInven = nil,
    rdo_pearlInven = nil,
    stc_pearlInvenEffect = nil,
    stc_selectbar = nil,
    stc_topItemSortBG = nil,
    check_itemSort = nil,
    txt_capacity = nil,
    stc_mainSlotBG = nil,
    scroll_inven = nil,
    stc_scrollArea = nil,
    template_slotBG = nil,
    template_slot = nil,
    template_lockSlot = nil,
    template_plusSlot = nil,
    template_onlyPlus = nil,
    stc_weightBG = nil,
    btn_buyWeight = nil,
    progress_weight = nil,
    progress_equipment = nil,
    stc_weightIcon = nil,
    txt_weightValue = nil,
    stc_weightTooltipBG = nil,
    txt_weightDesc = nil,
    txt_equipDesc = nil,
    txt_moneyDesc = nil,
    stc_moneyBG = nil,
    stc_moneyIcon = nil,
    txt_moneyValue = nil,
    stc_pearlIcon = nil,
    txt_pearlValue = nil,
    stc_mileageIcon = nil,
    txt_mileageValue = nil,
    stc_oceanIcon = nil,
    txt_oceanValue = nil,
    stc_buttonBG = nil,
    btn_alchemyFigureHead = nil,
    btn_alchemyStone = nil,
    btn_manufacture = nil,
    btn_dyePalette = nil,
    btn_trash = nil,
    btn_openEquip = nil,
    txt_enchantNumber = nil,
    stc_puzzleNotice = nil,
    txt_puzzleNoticeText = nil,
    stc_manufactureButtonBG = nil,
    btn_manufactureOpen = nil,
    btn_productNote = nil,
    stc_exchangeButtonBG = nil,
    btn_waypoint = nil,
    btn_widget = nil
  },
  slotConfig = {
    createIcon = true,
    createBorder = true,
    createCount = true,
    createEnchant = true,
    createCooltime = true,
    createExpiration = true,
    createExpirationBG = true,
    createExpiration2h = true,
    createClassEquipBG = true,
    createEnduranceIcon = true,
    createCooltimeText = true,
    createCash = true,
    createItemLock = true,
    createBagIcon = true,
    createSoulComplete = true,
    isTranslation = true
  },
  config = {
    slotCount = 64,
    slotCols = 8,
    slotRows = 0,
    slotStartX = 10,
    slotStartY = 150,
    slotGapX = 54,
    slotGapY = 54,
    slotEnchantX = 13,
    slotEnchantY = 76
  },
  _eIconTooltipType = {mileage = 0, oceanMoney = 1},
  effectScene = {
    newItem = {}
  },
  slotOverEffect = nil,
  _slotsBackground = Array.new(),
  slots = Array.new(),
  slotEtcData = {},
  newItemData = {},
  newPearlItemData = {},
  INVEN_MAX_COUNT = 192,
  INVEN_MAX_SLOTNO = 194,
  INVEN_CURRENTSLOT_COUNT = 64,
  _hasWeaponBlackStone = false,
  _hasArmorBlackStone = false,
  _hasSocketItem = false,
  _defaultPosX = 0,
  _defaultPosY = 0,
  _defaultSizeY = 0,
  _tempPosX = 0,
  _tempPosY = 0,
  _deleteWhereType = nil,
  _deleteSlotNo = nil,
  _deleteItemCount = nil,
  _deleteItemName = nil,
  _tooltipWhereType = nil,
  _tooltipSlotNo = nil,
  _isFirstTab = true,
  _isItemLockContentsOpen = true,
  _startSlotIndex = 0,
  _inventoryDragNoUsePanel = nil,
  _isMarketOpen = false,
  _isNormalInven = false,
  _openUiType = nil,
  _isFirstSummonItemUse = false,
  _isValuePackageItemUse = false,
  _whereUseItemSlotNo = nil,
  _whereUseItemSSW = nil,
  _exchangeSlotNo = {},
  _exchangeIndex = -1,
  filterFunc = nil,
  rClickFunc = nil,
  otherWindowOpenFunc = nil,
  effect = nil,
  _defaultTrashSpanY = 0,
  _defaultMoneySpanY = 0,
  _defaultWeightSpanY = 0,
  _defaultWeightTooltipSizeY = 0,
  _puzzleControlSlotNo = nil,
  _clickOutManufactreBG = false,
  _clickOutExchangeBG = false,
  _isConsole = false,
  _initialize = false
}
runLua("UI_Data/Script/Window/Inventory/Panel_Window_Inventory_All_1.lua")
runLua("UI_Data/Script/Window/Inventory/Panel_Window_Inventory_All_2.lua")
runLua("UI_Data/Script/Window/Inventory/Panel_Window_Inventory_All_3.lua")
runLua("UI_Data/Script/Window/Inventory/Panel_Window_Inventory_All_4.lua")
runLua("UI_Data/Script/Window/Inventory/Panel_Window_Inventory_All_5.lua")
registerEvent("FromClient_luaLoadComplete", "FromClient_Inventory_All_Init")
function FromClient_Inventory_All_Init()
  PaGlobal_Inventory_All:initialize()
end
