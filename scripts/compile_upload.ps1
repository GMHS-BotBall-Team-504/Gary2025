Clear-Host

# Initialize progress bar function
function Show-Progress {
    param (
        [int]$progress,
        [int]$total
    )
    $percent = [math]::Floor(($progress * 100) / $total)
    $width = 50
    $filled = [math]::Floor(($width * $progress) / $total)
    $empty = $width - $filled

    $bar = "=" * $filled + " " * $empty
    Write-Host "`r[$bar] $($percent.ToString("D3"))%" -NoNewline
}

# Define directories and variables
$scriptPath = $MyInvocation.MyCommand.Path
$BASE_DIR = Split-Path -Parent $scriptPath
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
$TOTAL_STEPS = $EXECUTABLES.Count + 1
$CURRENT_STEP = 0

# Initial progress display
Show-Progress $CURRENT_STEP $TOTAL_STEPS

# Move up one directory
Set-Location (Join-Path $BASE_DIR "..")
$CURRENT_STEP++
Show-Progress $CURRENT_STEP $TOTAL_STEPS
Start-Sleep -Milliseconds 100

# Remove build directory if exists
if (Test-Path $BUILD_DIR) {
    Remove-Item -Path $BUILD_DIR -Recurse -Force
}
$CURRENT_STEP++
Show-Progress $CURRENT_STEP $TOTAL_STEPS
Start-Sleep -Milliseconds 100

# Create build directory
New-Item -Path $BUILD_DIR -ItemType Directory -Force | Out-Null
$CURRENT_STEP++
Show-Progress $CURRENT_STEP $TOTAL_STEPS
Start-Sleep -Milliseconds 100

# Copy include and src
Copy-Item -Path "include" -Destination $BUILD_DIR -Recurse -Force
Copy-Item -Path "src" -Destination $BUILD_DIR -Recurse -Force
Start-Sleep -Milliseconds 100

# Build executables using a loop
for ($i = 0; $i -lt $EXECUTABLES.Count; $i++) {
    $EXECUTABLE = $EXECUTABLES[$i]
    $SOURCE_FILES = $SRC_FILES[$i]

    docker run -it --rm `
        --volume "${PWD}\out\build:/home/kipr:rw" `
        sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall -pthread `
        $SOURCE_FILES -lkipr -lm -o "/home/kipr/$EXECUTABLE" *> $null

    $CURRENT_STEP++
    Show-Progress $CURRENT_STEP $TOTAL_STEPS
    Start-Sleep -Milliseconds 100
}

# Deploy executables
# Since Windows doesn't have sshpass, we'll use the native scp client
# Create a temporary file with the password
$passwordFile = [System.IO.Path]::GetTempFileName()
Set-Content -Path $passwordFile -Value $KIPR_ROBOT_PASS -NoNewline

try {
    # Using pscp from PuTTY (needs to be installed and in PATH)
    pscp -r -pw $KIPR_ROBOT_PASS `
        "${BUILD_DIR}\*" "${KIPR_ROBOT_USER}@${KIPR_ROBOT_IP}:${DEPLOY_DIR}"
}
catch {
    Write-Host "`nError: Failed to use pscp. Make sure PuTTY tools are installed." -ForegroundColor Red
    Write-Host "Alternatively, you can use OpenSSH's scp (you'll be prompted for password):"
    Write-Host "scp -r ${BUILD_DIR}\* ${KIPR_ROBOT_USER}@${KIPR_ROBOT_IP}:${DEPLOY_DIR}"
    Write-Host "Password: $KIPR_ROBOT_PASS"
}
finally {
    # Remove the temporary password file
    if (Test-Path $passwordFile) {
        Remove-Item -Path $passwordFile -Force
    }
}

$CURRENT_STEP++
Show-Progress $CURRENT_STEP $TOTAL_STEPS
Start-Sleep -Milliseconds 100

Write-Host ""