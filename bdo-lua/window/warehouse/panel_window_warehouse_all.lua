PaGlobal_WareHouse_All = {
  _ui = {
    _pc = {
      _btn_close = nil,
      _btn_question = nil,
      _chk_itemSort = nil,
      _btn_Search = nil
    },
    _console = {
      _txt_Search = nil,
      _txt_keyGuideSort = nil,
      _txt_keyGuideClose = nil,
      _txt_keyGuideSelect = nil,
      _txt_keyGuideSilver = nil,
      _txt_keyGuideManufacture = nil
    },
    _stc_title = nil,
    _stc_decoBg = nil,
    _txt_villageName = nil,
    _txt_moneyTitle = nil,
    _txt_assetTitle = nil,
    _txt_valueMoney = nil,
    _txt_valueAsset = nil,
    _txt_capacity = nil,
    _btn_money = nil,
    _btn_asset = nil,
    _stc_itemSlotFrame = nil,
    _stc_itemSlotBg = nil,
    _stc_lockIcon = nil,
    _stc_multipleSelect = nil,
    _scroll_warehouse = nil,
    _btn_deliveryInfomation = nil,
    _btn_itemMarketRegist = nil,
    _btn_manufacture = nil,
    _btn_guildUpdate = nil,
    _stc_topBg = nil,
    _stc_rightBg = nil,
    _stc_leftBg = nil,
    _stc_bottomBg = nil,
    _stc_moneyBg = nil,
    _list2_serchWareHouse = nil,
    _txt_notAvaliable = nil
  },
  _slotConfig = {
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
    createCash = true,
    createBagIcon = true,
    createEnduranceIcon = true,
    createCheckBox = true,
    isTranslation = true
  },
  _config = {
    slotCount = 90,
    slotCols = 9,
    slotRows = 0,
    slotStartX = 5,
    slotStartY = 5,
    slotGapX = 51,
    slotGapY = 51
  },
  _blankSlots = Array.new(),
  _slots = Array.new(),
  _slotNilEffect = {},
  _slotFilterEffect = {},
  _warehouseTitle = PAGetString(Defines.StringSheet_RESOURCE, "PANEL_WORLDMAP_RIGHTMENU_WAREHOUSE_TITLE"),
  _currentWaypointKey = 0,
  _currentRegionName = "None",
  _fromType = CppEnums.WarehoouseFromType.eWarehoouseFromType_Worldmap,
  _installationActorKeyRaw = 0,
  _targetActorKeyRaw = nil,
  _deleteSlotNo = nil,
  _s64_deleteCount = Defines.s64_const.s64_0,
  _startSlotIndex = 0,
  _tooltipSlotNo = nil,
  _myAsset = toInt64(0, 0),
  itemMarketFilterFunc = nil,
  itemMarketRclickFunc = nil,
  manufactureFilterFunc = nil,
  manufactureRclickFunc = nil,
  addSizeY = 0,
  savedWayPointKey = 0,
  _btnMarketRegistSizeX = 0,
  _btnMarketRegSpanSizeY = 0,
  _panelSizeY = 0,
  _assetTitlePosY = 0,
  _assetValuePosY = 0,
  _staticCapacityPosY = 0,
  _moneyValuePosY = 0,
  _invenSizeX = 477,
  _warehouseProductWaypoint = {
    [0] = 1,
    61,
    301,
    302,
    601,
    602,
    608,
    1101,
    1141,
    1301,
    1314,
    1319,
    1623,
    1604,
    604,
    1380,
    1649,
    1691,
    1002,
    1343
  },
  _warehouseInfo = {
    _territoryCount = 0,
    _territoryGroup = {}
  },
  _territoryNameInfo = {},
  _currentTerritoryKey = -1,
  _maxTerritoryKeyCount = 10,
  _separatorNumber = 100,
  _selectWaypointKey = -1,
  _rightBgOffset = 15,
  _beforePanelSizeX = 1010,
  _defaultRightBgSize = {x = 0, y = 0},
  _defaultMoneyBgSize = {x = 0, y = 0},
  _isConsole = false,
  _isSorted = false,
  _keyGuide = {},
  _buttonData = {
    selectItem = false,
    marketRegist = true,
    manufacture = true,
    delivery = true,
    guildUpdate = true,
    sendMoney = true
  },
  _maxFindItemCnt = 0,
  _findItemIdx = {},
  _initialize = false
}
runLua("UI_Data/Script/Window/WareHouse/Panel_Window_WareHouse_All_1.lua")
runLua("UI_Data/Script/Window/WareHouse/Panel_Window_WareHouse_All_2.lua")
registerEvent("FromClient_luaLoadComplete", "FromClient_WareHouseInit")
function FromClient_WareHouseInit()
  PaGlobal_WareHouse_All:initialize()
end
