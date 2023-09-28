@echo off
@icacls %1 /grant:r %username%:F /T /C /L /Q
@echo Done.
