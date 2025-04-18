Clear-Host

# Initialize progress bar function
function Show-ProgressBar {
    param (
        [int]$Progress,
        [int]$Total
    )
    $width = 50
    $percent = [math]::Floor(($Progress * 100) / $Total)
    $filled = [math]::Floor(($width * $Progress) / $Total)
    $empty = $width - $filled

    $bar = "=" * $filled + " " * $empty
    Write-Host "`r[$bar] $percent%" -NoNewline
}

# Define directories and variables
$BASE_DIR = Split-Path -Parent $MyInvocation.MyCommand.Path
$BUILD_DIR = Join-Path $BASE_DIR "out\build"
$KIPR_ROBOT_IP = "10.0.0.250"
$KIPR_ROBOT_USER = "kipr"
$KIPR_ROBOT_PASS = "botball"
$DEPLOY_DIR = "/home/kipr/trison"
$SRC_DIR = Join-Path $BASE_DIR "src"

# Array of executables to build
$EXECUTABLES = @("manual", "auto", "main", "start")
$SRC_FILES = @(
    "src/manual.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c",
    "src/auto.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c",
    "src/main.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c",
    "src/start.c"
)
$TOTAL_STEPS = $EXECUTABLES.Count + 3
$CURRENT_STEP = 0

# Initial progress display
Show-ProgressBar $CURRENT_STEP $TOTAL_STEPS

# Move up one directory
Set-Location (Join-Path $BASE_DIR "..")
$CURRENT_STEP++
Show-ProgressBar $CURRENT_STEP $TOTAL_STEPS
Start-Sleep -Milliseconds 100

# Remove build directory if it exists
if (Test-Path $BUILD_DIR) {
    Remove-Item $BUILD_DIR -Recurse -Force
}
$CURRENT_STEP++
Show-ProgressBar $CURRENT_STEP $TOTAL_STEPS
Start-Sleep -Milliseconds 100

# Create build directory
New-Item -Path $BUILD_DIR -ItemType Directory -Force | Out-Null
$CURRENT_STEP++
Show-ProgressBar $CURRENT_STEP $TOTAL_STEPS
Start-Sleep -Milliseconds 100

# Copy include and src
Copy-Item -Path "include" -Destination $BUILD_DIR -Recurse -Force
Copy-Item -Path "src" -Destination $BUILD_DIR -Recurse -Force
Start-Sleep -Milliseconds 100

# Build executables using a loop
for ($i = 0; $i -lt $EXECUTABLES.Count; $i++) {
    $EXECUTABLE = $EXECUTABLES[$i]
    $SOURCE_FILES = $SRC_FILES[$i]

    # Convert Windows path to Docker path format
    $BUILD_DIR_DOCKER = $BUILD_DIR.Replace("\", "/").Replace(":", "")
    $BUILD_DIR_DOCKER = "/$BUILD_DIR_DOCKER"

    # Run Docker command
    docker run -it --rm `
        --volume "${PWD}/out/build:/home/kipr:rw" `
        sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall -pthread `
        $SOURCE_FILES -lkipr -lm -o "/home/kipr/$EXECUTABLE" | Out-Null

    $CURRENT_STEP++
    Show-ProgressBar $CURRENT_STEP $TOTAL_STEPS
    Start-Sleep -Milliseconds 100
}

Write-Host "`n"