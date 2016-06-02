-- flute: fast lightweight ultimate text editor
-- Copyright (C) 2016  David Ulrich
--
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU Affero General Public License as published
-- by the Free Software Foundation, version 3 of the License.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU Affero General Public License for more details.
--
-- You should have received a copy of the GNU Affero General Public License
-- along with this program.  If not, see <http://www.gnu.org/licenses/>.

require "config/config"

local curses = require "curses"
local screen = curses.initscr()

local KEY = {
	ENTER = 10,
	ESC   = 27,
	
	UP    = 259,
	DOWN  = 258,
	LEFT  = 260,
	RIGHT = 261,
	
	HOME   = 262,
	END    = 360,
	
	DELETE = 330,
	BSPACE = 263
}

local MODE_T = {
	EDIT = 0,
	CMD  = 1,
	FIND = 2
}
local MODE = MODE_T.EDIT

local layout = {}
layout[MODE_T.EDIT] = {
	origin = { x = 0, y = 0 },
	height = -1
}
layout[MODE_T.CMD] = {
	origin = { x = 0, y = -1 },
	height = 1
}
layout[MODE_T.FIND] = {
	origin = { x = 0, y = -1 },
	height = 1
}

local settings = {
	auto_indent = 0
}

local state = {
	buffer = {},
	cmd = "",
	find = {
		search  = "",
		replace = ""
	},
	cursor = {
		pos_edit_0 = { x = 0, y = 0 }, -- selection start
		pos_edit_1 = { x = 0, y = 0 }, -- selection end
		
		pos_cmd_0  = { x = 0, y = 0 },
		pos_cmd_1  = { x = 0, y = 0 },
		
		pos_find_0 = { x = 0, y = 0 },
		pos_find_1 = { x = 0, y = 0 }
	},
	insert = 0
}
state.buffer[0] = ""

function cprint(str)
	str = str or ""
	
	screen:clrtoeol()
	screen:addstr(str)
end

function cmd_print(str)
	local y, x
	
	y, x = screen:getmaxyx()
	
	screen:move(y - 1, 0)
	
	cprint(str)
	
	screen:move(y - 1, state.cursor.pos_cmd_0.x + 2)
end

function line_print(y)
	y = y or state.cursor.pos_edit_0.y
	
	screen:move(y, 0)
	
	cprint(state.buffer[y])
	
	screen:move(state.cursor.pos_edit_0.y, state.cursor.pos_edit_0.x)
end


local function cmd_exec(cmd)
	if cmd == "exit" then
		return 1
	else
		-- execute the command
		state.cursor.pos_cmd_0.x = 0
		return 0
	end
end

local function delete_char()
	if MODE == MODE_T.EDIT then
		if state.buffer[state.cursor.pos_edit_0.y] ~= "" and state.cursor.pos_edit_0.x ~= 0 then
			state.buffer[state.cursor.pos_edit_0.y] = state.buffer[state.cursor.pos_edit_0.y]:sub(0, state.cursor.pos_edit_0.x - 1) .. state.buffer[state.cursor.pos_edit_0.y]:sub(state.cursor.pos_edit_0.x + 1)
			state.cursor.pos_edit_0.x = state.cursor.pos_edit_0.x - 1
		end
	elseif MODE == MODE_T.FIND then
		
	elseif MODE == MODE_T.CMD then
		if state.cmd ~= "" and state.cursor.pos_cmd_0.x ~= 0 then
			state.cmd = state.cmd:sub(0, state.cursor.pos_cmd_0.x - 1) .. state.cmd:sub(state.cursor.pos_cmd_0.x + 1)
			state.cursor.pos_cmd_0.x = state.cursor.pos_cmd_0.x - 1
		end
	end
end

local function get_indent_chars()
	if settings.auto_indent == 0 then
		return ""
	else
		-- call language indenting function, or check current level for generic
		return ""
	end
end

local function insert_char(input)
	if MODE == MODE_T.EDIT then
		if state.buffer[state.cursor.pos_edit_0.y] == "" or state.cursor.pos_edit_0.x == 0 then
			state.buffer[state.cursor.pos_edit_0.y] = string.char(input) .. state.buffer[state.cursor.pos_edit_0.y]
		else
			state.buffer[state.cursor.pos_edit_0.y] = state.buffer[state.cursor.pos_edit_0.y]:sub(0, state.cursor.pos_edit_0.x) .. string.char(input) .. state.buffer[state.cursor.pos_edit_0.y]:sub(state.cursor.pos_edit_0.x + 1)
		end
		state.cursor.pos_edit_0.x = state.cursor.pos_edit_0.x + 1
	elseif MODE == MODE_T.FIND then
		
	elseif MODE == MODE_T.CMD then
		if state.cmd == "" or state.cursor.pos_cmd_0.x == 0 then
			state.cmd = string.char(input) .. state.cmd
		else
			state.cmd = state.cmd:sub(0, state.cursor.pos_cmd_0.x) .. string.char(input) .. state.cmd:sub(state.cursor.pos_cmd_0.x + 1)
		end
		state.cursor.pos_cmd_0.x = state.cursor.pos_cmd_0.x + 1
	end
end

local function shift_buffer()
	for i = (#state.buffer + 1), (state.cursor.pos_edit_0.y + 1), -1 do
		state.buffer[i] = state.buffer[i - 1]
		line_print(i)
	end
end


local function main()
	local input
	
	curses.cbreak()
	curses.echo(false)
	curses.nl(0)
	curses.keypad()
	-- redraw()
	
	while true do
		input = screen:getch()
		
		-- redraw()
		
		if input == 96 and MODE ~= MODE_T.CMD then
			MODE = MODE_T.CMD
			input = 0
			-- draw cmd line
		elseif input == 6 then
			MODE = MODE_T.FIND
			input = 0
			-- draw find line|
		elseif input == KEY.ESC then
			MODE = MODE_T.EDIT
			input = 0
			-- draw status line
			-- reset cursor to pos_edit_*
		end
		
		if MODE == MODE_T.CMD then
			if input == KEY.ENTER then
				if cmd_exec(state.cmd) == 1 then
					curses.endwin()
					break
				end
				state.cmd = ""
			elseif input == KEY.LEFT then
				state.cursor.pos_cmd_0.x = math.max(state.cursor.pos_cmd_0.x - 1, 0)
			elseif input == KEY.RIGHT then
				state.cursor.pos_cmd_0.x = math.min(state.cursor.pos_cmd_0.x + 1, #state.cmd)
			elseif input == KEY.BSPACE then
				delete_char()
			elseif input == 0 then
				-- nothing
			elseif input >= 32 and input <= 124 then
				insert_char(input)
			end
			cmd_print(": " .. state.cmd)
		elseif MODE == MODE_T.FIND then
			-- find / replace
		else -- EDIT
			if input == KEY.ENTER then
				-- if selection delete it
				-- insert a line, shift the buffer down
				state.cursor.pos_edit_0.y = state.cursor.pos_edit_0.y + 1
				shift_buffer()
				state.buffer[state.cursor.pos_edit_0.y] = get_indent_chars()
				state.cursor.pos_edit_0.x = math.min(state.cursor.pos_edit_0.x, #state.buffer[state.cursor.pos_edit_0.y])
			elseif input == KEY.UP then
				state.cursor.pos_edit_0.y = math.max(state.cursor.pos_edit_0.y - 1, 0)
				state.cursor.pos_edit_0.x = math.min(state.cursor.pos_edit_0.x, #state.buffer[state.cursor.pos_edit_0.y])
			elseif input == KEY.DOWN then
				state.cursor.pos_edit_0.y = math.min(state.cursor.pos_edit_0.y + 1, #state.buffer)
				state.cursor.pos_edit_0.x = math.min(state.cursor.pos_edit_0.x, #state.buffer[state.cursor.pos_edit_0.y])
			elseif input == KEY.LEFT then
				state.cursor.pos_edit_0.x = math.max(state.cursor.pos_edit_0.x - 1, 0)
			elseif input == KEY.RIGHT then
				state.cursor.pos_edit_0.x = math.min(state.cursor.pos_edit_0.x + 1, #state.buffer[state.cursor.pos_edit_0.y])
			elseif input == KEY.BSPACE then
				-- if selection delete it
				-- else delete one char
				delete_char()
			elseif input == 0 then
				-- nothing
			elseif input >= 32 and input <= 124 then
				insert_char(input)
			end
			cmd_print("pressed: " .. curses.keyname(input) .. " [" .. input .. "] " .. state.cursor.pos_edit_0.y .. ", " .. state.cursor.pos_edit_0.x)
			line_print()
		end
	end
	
end

local function err (err)
	curses.endwin ()
	print "Caught an error:"
	print (debug.traceback (err, 2))
	os.exit (2)
end

xpcall(main, err)
