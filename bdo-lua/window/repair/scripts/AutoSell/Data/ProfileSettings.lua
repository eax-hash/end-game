ProfileSettings = {}
ProfileSettings.__index = ProfileSettings

setmetatable(ProfileSettings, {
	__call = function(cls, ...)
		return cls.new(...)
	end
})

function ProfileSettings.new()
	local self = setmetatable({}, ProfileSettings)

	self.Name = ""

	self.Inventory = {}
	self.Inventory.Sell = {Enabled = true}
	self.Inventory.Items = {}

	return self
end
