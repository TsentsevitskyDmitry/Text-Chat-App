#include "StatusViewController.h"
#include <windows.h>
#include <tchar.h>

void StatusViewController::alert(std::string text)
{
    if(alertCallback){
        alertCallback(text);
    }
}

void StatusViewController::updateButtonPressed()
{
    ServerInfo info;
    helper.getStatus(info);
    if(dataArrived){
        dataArrived(info);
    }
}

void StatusViewController::installButtonPressed(std::wstring path)
{
    SC_HANDLE hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_CREATE_SERVICE);
    if(!hSCManager) {
      alert("Error: Can't open Service Control Manager");
      return;
    }

    SC_HANDLE hService = CreateService(
       hSCManager,
       SERVICE_NAME,
       SERVICE_NAME,
       SERVICE_ALL_ACCESS,
       SERVICE_WIN32_OWN_PROCESS,
       SERVICE_DEMAND_START,
       SERVICE_ERROR_NORMAL,
       path.c_str(),
       nullptr, nullptr, nullptr, nullptr, nullptr
    );

    if(!hService) {
      DWORD err = GetLastError();
      switch(err) {
        case ERROR_ACCESS_DENIED:
          alert("Error: ERROR_ACCESS_DENIED");
          break;
        case ERROR_CIRCULAR_DEPENDENCY:
          alert("Error: ERROR_CIRCULAR_DEPENDENCY");
          break;
        case ERROR_DUPLICATE_SERVICE_NAME:
          alert("Error: ERROR_DUPLICATE_SERVICE_NAME");
          break;
        case ERROR_INVALID_HANDLE:
          alert("Error: ERROR_INVALID_HANDLE");
          break;
        case ERROR_INVALID_NAME:
          alert("Error: ERROR_INVALID_NAME");
          break;
        case ERROR_INVALID_PARAMETER:
          alert("Error: ERROR_INVALID_PARAMETER");
          break;
        case ERROR_INVALID_SERVICE_ACCOUNT:
          alert("Error: ERROR_INVALID_SERVICE_ACCOUNT");
          break;
        case ERROR_SERVICE_EXISTS:
          alert("Error: ERROR_SERVICE_EXISTS");
          break;
        default:
          alert("Error: Undefined");
      }
      CloseServiceHandle(hSCManager);
      return;
    }
    CloseServiceHandle(hService);

    CloseServiceHandle(hSCManager);
    alert("Success install service!");

    startButtonPressed();
}

void StatusViewController::stopButtonPressed()
{
    SERVICE_STATUS_PROCESS ssp;
    DWORD dwStartTime = GetTickCount();
    DWORD dwBytesNeeded;
    DWORD dwTimeout = 30000; // 30-second time-out

    SC_HANDLE hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if(!hSCManager) {
       alert("Error: Can't open Service Control Manager");
       return;
    }
    SC_HANDLE hService = OpenService(hSCManager, SERVICE_NAME, SERVICE_STOP | SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS);
    if(!hService) {
       alert("Error: Can't remove service");
       CloseServiceHandle(hSCManager);
       return;
    }

    if ( !ControlService(hService, SERVICE_CONTROL_STOP, reinterpret_cast<LPSERVICE_STATUS>(&ssp) )){
        alert("ControlService failed: " + std::to_string(GetLastError()));
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return;
    }

    // Wait for the service to stop.
    while ( ssp.dwCurrentState != SERVICE_STOPPED )
    {
        Sleep( ssp.dwWaitHint );
        if (!QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded)) {
            alert("ControlService failed: " + std::to_string(GetLastError()));
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return;
        }

        if ( ssp.dwCurrentState == SERVICE_STOPPED )
            break;

        if ( GetTickCount() - dwStartTime > dwTimeout)
        {
            alert( "Wait timed out\n" );
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return;        }
    }
    alert("Service stopped successfully\n");

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);

    Sleep(100);
    updateButtonPressed();
}

void StatusViewController::removeButtonPressed()
{
    stopButtonPressed();

    SC_HANDLE hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if(!hSCManager) {
       alert("Error: Can't open Service Control Manager");
       return;
    }
    SC_HANDLE hService = OpenService(hSCManager, SERVICE_NAME, SERVICE_STOP | DELETE);
    if(!hService) {
       alert("Error: Can't remove service");
       CloseServiceHandle(hSCManager);
       return;
    }

    DeleteService(hService);
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);

    alert("Success remove service!");
    Sleep(100);
    updateButtonPressed();
}


void StatusViewController::startButtonPressed()
{
    SC_HANDLE hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_CREATE_SERVICE);
    SC_HANDLE hService = OpenService(hSCManager, SERVICE_NAME, SERVICE_START);
    if(!StartService(hService, 0, nullptr)) {
      CloseServiceHandle(hSCManager);
      alert("Error: Can't start service: error " + std::to_string(GetLastError()));
      return;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    alert("Service started successfully\n");

    Sleep(100);
    updateButtonPressed();
  }

void StatusViewController::setDataArrivedCallback(std::function<void (ServerInfo &)> callback)
{
    dataArrived = callback;
}

void StatusViewController::setAlertCallback(std::function<void (std::string&)> callback)
{
    alertCallback = callback;
}
