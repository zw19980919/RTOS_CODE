set_project("RTOS") --设置工程名称
set_version("0.0.2", {build = "%Y%m%d%H%M"})--设置版本历史
set_xmakever("2.7.8")--设置xmake最低版本
add_rules("mode.release", "mode.debug")--添加规则？
-----------------------------------------------------------------------------------------


---------------------------------set exe or binary name----------------------------------
local USER_PROJECT_NAME = "RTOS"   --default project_name---------------------------------


--print(USER_PROJECT_NAME)
TOP_DIR  = os.curdir()----------------------------------------------得到顶层的xmake.lua路径
-------------------------------------------------------------------print(USER_PROJECT_NAME)

--------------------------------------操作编译选项，选择哪个编译器和目标机器-------------------
option("win") --构建选项
    set_default(false )--默认true
    set_showmenu(true)--显示菜单·
    set_category("win")--设置分类选项
    set_description("Enable or disable win Plat", "  =y|n")--描述信息
option_end()--构建选项结束
--------------------------------------------------------------------------------------------
set_config("plat", "linux")

includes(TOP_DIR .. "/code")--包含project目录
---------------------------------------------------------------------------------------------
local TARGET_NAME = "ring_buffer_test"

target(TARGET_NAME)

    	set_kind("binary")
		add_deps("RTOS")--设置依赖，这个依赖是另外的target
        add_files("main.c")
        add_ldflags(" /usr/lib/x86_64-linux-gnu/libpthread-2.31.so ",{force = true })
	
target_end()
