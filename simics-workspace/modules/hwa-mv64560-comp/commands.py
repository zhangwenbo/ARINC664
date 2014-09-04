import cli

class_name = 'hwa-mv64560-comp'

# info command prints static information
def get_info(obj):
    return []

# status command prints dynamic information
def get_status(obj):
    return [("Registers",
             [("Value", obj.value)])]

cli.new_info_command(class_name, get_info)
cli.new_status_command(class_name, get_status)
