function getCurrentOS() {
    const system = process.platform;
    let result;
    switch (system) {
        case "linux":
            result = "Superior OS";
            break;
        case "win32":
            result = "Inferior OS";
            break;
        default:
            result = "Mediocre OS";
    }
    return result;
}

console.log(getCurrentOS());