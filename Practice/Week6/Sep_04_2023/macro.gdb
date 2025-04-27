define myMacro
    info breakpoints
    run
end

define custom-print
    set $var = 0
    printf "Custom Data: %d\n", $var
end


# if/while $condition
# # Code to execute if condition is true
# end
# 
# shell echo "This is a shell command"
# 
# source another_script.gdb
# 
# print $my_variable
#
# set $var = $arg0
# custom-command arg0