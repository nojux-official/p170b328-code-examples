import platform


def get_current_os():
    platform_system = platform.system()
    if platform_system == "Linux":
        return "Superior OS"
    elif platform_system == "Windows":
        return "Inferior OS"
    else:
        return "Mediocre OS"


print(get_current_os())

