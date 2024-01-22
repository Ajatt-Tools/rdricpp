add_rules("mode.debug", "mode.release")
set_languages("c++2b")
set_warnings("allextra", "error")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "build"})

if is_mode("debug") then
    add_defines("DEBUG")
    set_symbols("debug")
    set_optimize("none")
    set_policy("build.sanitizer.address", true)
    set_policy("build.sanitizer.undefined", true)
elseif is_mode("release") then
    add_defines("NDEBUG")
    set_optimize("faster") -- Arch Linux builds its packages with -O2
    add_cxflags("-fstack-protector-strong", "-fstack-clash-protection")
end

local format = function(target)
    import("lib.detect.find_program")
    local clang_format = find_program("clang-format")
    if not clang_format then
        return print("Skipped clang-format run for target: %s", target:name())
    end
    local paramlist = {"--sort-includes", "-i"}
    for _, file in pairs(target:headerfiles()) do
        table.insert(paramlist, file)
    end
    for _, file in pairs(target:sourcefiles()) do
        table.insert(paramlist, file)
    end
    os.execv(clang_format, paramlist)
    print("Finished clang-format for target: %s", target:name())
end

-- Library
target("rdricpp")
    add_includedirs("src")
    add_headerfiles("src/types.h", "src/rdricpp.h", {prefixdir = "rdricpp"})
    set_kind("static")
    add_files("src/*.cpp")
    remove_files("src/main.cpp")
    -- Run clang-format before build
    before_build(format)
target_end()

-- Main
target("main")
    set_kind("binary")
    add_files("src/*.cpp")
    add_deps("rdricpp")
target_end()

-- Tests
-- xmake f --tests=y
-- xmake run tests
option("tests", {default = false, description = "Enable tests"})

if has_config("tests") then
    add_requires("catch2 3.x")

    -- Tests target
    target("tests")
        set_kind("binary")
        add_packages("catch2")
        add_files("src/*.cpp", "tests/*.cpp")
        remove_files("src/main.cpp")
        add_headerfiles("src/*.h")
        add_includedirs("src")

        -- Run clang-format before build
        before_build(format)

        before_run(function (target)
            print("Running unit tests on target: %s", target:name())
        end)
    target_end()
end
