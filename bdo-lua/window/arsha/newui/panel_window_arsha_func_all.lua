PaGlobal_Arsha_Func_All = {
  _ui = {
    stc_titleArea = nil,
    txt_title = nil,
    stc_decoImg = nil,
    btn_close = nil,
    stc_radioMenu = nil,
    rdo_gameSetting = nil,
    rdo_teamSetting = nil,
    stc_selectBar = nil,
    btn_gameStart = nil,
    btn_gameStop = nil,
    btn_allResurrection = nil,
    _gameSet = {
      stc_mainBg = nil,
      stc_gameTypeBg = nil,
      txt_gameTypeTitle = nil,
      rdo_gameType = {},
      stc_gameLevelBg = nil,
      txt_gameLevelTitle = nil,
      rdo_gameLevel = {},
      stc_gameRoundBg = nil,
      txt_gameRoundTitle = nil,
      rdo_gameRound = {},
      stc_gameLifeTeamBg = nil,
      txt_gameLifeTitle = nil,
      rdo_gameLife = {},
      stc_gameTimeBg = nil,
      txt_gameTimeTitle = nil,
      rdo_gameTime = {},
      stc_gameMemberBg = nil,
      txt_gameMemberTitle = nil,
      rdo_gameMember = {}
    },
    _attenderSet = {
      stc_mainBg = nil,
      stc_leftAreaBg = nil,
      chk_lock = nil,
      txt_gameTypeName = nil,
      txt_limitTimeTitle = nil,
      txt_limitLevelTitle = nil,
      txt_roundTitle = nil,
      txt_limitTimeValue = nil,
      txt_limitLevelValue = nil,
      txt_roundValue = nil,
      stc_noAdminImg = nil,
      rdo_inviteWaiter = nil,
      rdo_inviteWatcher = nil,
      edit_inviteName = nil,
      btn_invite = nil,
      btn_inviteList = nil,
      stc_waitTeamBg = nil,
      stc_radioSubMenu = nil,
      rdo_waiter = nil,
      rdo_watcher = nil,
      stc_selectBar = nil,
      btn_exit = nil,
      btn_GoWait = nil,
      list2_waitList = nil,
      txt_waitLevelTitle = nil,
      txt_waitClassTitle = nil,
      txt_waitNameTitle = nil,
      stc_rightAreaBg = nil,
      list2_teamAList = nil,
      list2_teamBList = nil,
      stc_frameBgBlue = nil,
      stc_frameBgRed = nil,
      stc_frameBgYellow = nil,
      btn_GoTeamA = nil,
      btn_GoTeamB = nil,
      btn_teamATitleBg = nil,
      txt_levelATitle = nil,
      txt_classATitle = nil,
      txt_nameATitle = nil,
      btn_teamBTitleBg = nil,
      txt_levelBTitle = nil,
      txt_classBTitle = nil,
      txt_nameBTitle = nil,
      stc_teamAreaBg = nil,
      stc_teamAArea = nil,
      stc_teamAName = nil,
      btn_teamAEditName = nil,
      stc_teamBArea = nil,
      stc_teamBName = nil,
      btn_teamBEditName = nil,
      stc_teamVSicon = nil,
      stc_teamCenterLine = nil,
      stc_aloneAreaBg = nil,
      stc_aloneTeamA = nil,
      stc_aloneTeamB = nil,
      stc_aloneCenterLine = nil,
      txt_aloneLifeTeam = nil,
      txt_aloneLifeTeamValue = nil
    }
  },
  _ui_console = {
    stc_mainRadioLB = nil,
    stc_mainRadioRB = nil,
    stc_subRadioLB = nil,
    stc_subRadioRB = nil,
    stc_editGuideX = nil,
    stc_bottomKeyGuideBg = nil,
    stc_keyGuideY = nil,
    stc_keyGuideA = nil,
    stc_keyGuideB = nil
  },
  _ui_subMenu = {
    btn_kick = nil,
    btn_kickAll = nil,
    btn_teamChange = nil,
    btn_subMaster = nil,
    btn_teamMaster = nil,
    stc_keyGuideBg = nil,
    txt_keyGuideA = nil,
    txt_keyGuideB = nil
  },
  _notHostHideControl = Array.new(),
  _subHostShowControl = Array.new(),
  _gameSetMenuControl = Array.new(),
  _gameSetShowcontrol = Array.new(),
  _subMenuShowControl = Array.new(),
  _mainRadioMenu = {},
  _waitRadioMenu = {},
  _gameTypeStr = {
    [CppEnums.CompetitionMatchType.eCompetitionMatchMode_Round] = PAGetString(Defines.StringSheet_RESOURCE, "PANEL_ARSHA_TEAMMODE_TITLE"),
    [CppEnums.CompetitionMatchType.eCompetitionMatchMode_FreeForAll] = PAGetString(Defines.StringSheet_RESOURCE, "PANEL_ARSHA_ALIVEMODE_TITLE"),
    [CppEnums.CompetitionMatchType.eCompetitionMatchMode_Personal] = PAGetString(Defines.StringSheet_RESOURCE, "PANEL_ARSHA_PERSONALMODE_TITLE")
  },
  _menuType = {GAME = 1, ATTENDER = 2},
  _waitListType = {WAITER = 1, WATCHER = 2},
  _teamListType = {
    RED = 1,
    BLUE = 2,
    COUNT = 2
  },
  _setLevel = {
    [1] = 55,
    [2] = 60,
    [3] = 1
  },
  _setRound = {
    [1] = 1,
    [2] = 3,
    [3] = 5,
    [4] = 7
  },
  _setLife = {
    [1] = 1,
    [2] = 3,
    [3] = 5,
    [4] = 7
  },
  _setTime = {
    [1] = 1,
    [2] = 3,
    [3] = 5,
    [4] = 7
  },
  _setMember = {
    [1] = 1,
    [2] = 2,
    [3] = 3,
    [4] = 4
  },
  _baseSize = {
    leftList = {},
    rightList = {},
    edit_invite = {},
    panel = {},
    leftBg = {},
    leftListBg = {},
    rightListBg = {},
    aloneListBg = {},
    exitBtn = {},
    rightArea = {}
  },
  _basePos = {
    mainRadio = {},
    leftTitle = {},
    rightTitle = {}
  },
  _aloneViewDiffSize = {},
  _curMenu = 2,
  _curWaitList = 1,
  _curUpdateListIdx = 1,
  _curCompetitionMatchType = nil,
  _isWatcher = false,
  _isHost = false,
  _isOpen = false,
  _targetScore = 3,
  _lifeLimit = 1,
  _timeLimit = ToClient_CompetitionMatchTimeLimit(),
  _levelLimit = 55,
  _maxPartyMemberCount = 5,
  _maxWaitTime = 20,
  _isConsole = false,
  _initialize = false
}
runLua("UI_Data/Script/Window/Arsha/NewUI/Panel_Window_Arsha_Func_All_1.lua")
runLua("UI_Data/Script/Window/Arsha/NewUI/Panel_Window_Arsha_Func_All_2.lua")
registerEvent("FromClient_luaLoadComplete", "FromClient_Arsha_Func_All_Init")
function FromClient_Arsha_Func_All_Init()
  PaGlobal_Arsha_Func_All:initialize()
end
