#include <windows.h>
#include <initguid.h>
#include <ole2.h>
#include <mstask.h>
#include <msterr.h>
#include <objidl.h>
#include <wchar.h>
#include <stdio.h>

int main(int /*argc*/, char** /*argv*/)
{
  HRESULT hr = ERROR_SUCCESS;
  ITaskScheduler *pITS;
  
  
  /////////////////////////////////////////////////////////////////
  // Inicjalizacja biblioteki COM
  /////////////////////////////////////////////////////////////////
  hr = CoInitialize(NULL);

  if (SUCCEEDED(hr))
  {
     hr = CoCreateInstance(CLSID_CTaskScheduler,
                           NULL,
                           CLSCTX_INPROC_SERVER,
                           IID_ITaskScheduler,
                           (void **) &pITS);
     if (FAILED(hr))
     {
        CoUninitialize();
        return 1;
     }
  }
  else
  {
     return 1;
  }
  
  
  /////////////////////////////////////////////////////////////////
  // Wywolujemy ITaskScheduler::NewWorkItem() aby utworzyc nowe zadanie
  /////////////////////////////////////////////////////////////////
  LPCWSTR pwszTaskName;
  ITask *pITask;
  IPersistFile *pIPersistFile;
  pwszTaskName = L"Test Task1";
  
  hr = pITS->NewWorkItem(pwszTaskName,           // nazwa zadania
                         CLSID_CTask,            // identyfikator klasy 
                         IID_ITask,              // identyfikator interfejsu
                         (IUnknown**)&pITask); // adres wskaznika do interfejsu ITask
  
  
  pITS->Release();                               // Release object
  if (FAILED(hr))
  {
     CoUninitialize();
     fprintf(stderr, "Failed calling NewWorkItem, error = 0x%x\n",hr);
     return 1;
  }
  
  
  /////////////////////////////////////////////////////////////////
  // Wywolaj IUnknown::QueryInterface aby dostac wskaznik do 
  // IPersistFile i IPersistFile::Save aby zapisac zadanie na dysku
  /////////////////////////////////////////////////////////////////
  
  hr = pITask->QueryInterface(IID_IPersistFile,
                              (void **)&pIPersistFile);
  
  if (FAILED(hr))
  {
     CoUninitialize();
     fprintf(stderr, "Failed calling QueryInterface, error = 0x%x\n",hr);
     return 1;
  }
  
  
  hr = pIPersistFile->Save(NULL,
                           TRUE);
  pIPersistFile->Release();
  if (FAILED(hr))
  {
     CoUninitialize();
     fprintf(stderr, "Failed calling Save, error = 0x%x\n",hr);
     return 1;
  }
  


///////////////////////////////////////////////////
///////////tworzymy trigger////////////////////////
///////////////////////////////////////////////////

ITaskTrigger*   pITaskTrig = NULL;
IPersistFile*   pIFile     = NULL;
TASK_TRIGGER    rTrigger;
WORD            wTrigNumber;


 hr = pITask->CreateTrigger ( &wTrigNumber, &pITaskTrig );

    if ( FAILED (hr) )
        {
        fprintf(stderr, "Failed calling CreateTrigger, error = 0x%x\n",hr);
        return hr;
        }

	//wypelniamy strukture TASK_TRIGGER
	ZeroMemory ( &rTrigger, sizeof (TASK_TRIGGER) );

    rTrigger.cbTriggerSize = sizeof (TASK_TRIGGER);
    rTrigger.wBeginYear    = 2004;
    rTrigger.wBeginMonth   = 4;
    rTrigger.wBeginDay     = 10;
    rTrigger.wStartHour    = 10;
    rTrigger.wStartMinute  = 0;
	rTrigger.TriggerType = TASK_TIME_TRIGGER_ONCE;
	

	// skojarz Trigger z zadaniem
	hr = pITaskTrig->SetTrigger ( &rTrigger );

    if ( FAILED(hr) )
        {
        fprintf(stderr, "Failed calling SetTrigger, error = 0x%x\n",hr);
        return 1;
        }


    // zapisujemy zmiany w PersistFile
    hr = pITask->QueryInterface ( IID_IPersistFile, (void **) &pIFile );

    if ( FAILED (hr) )
        {
        fprintf(stderr, "Failed calling QueryInterface, error = 0x%x\n",hr);
        return 1;
        }

    hr = pIFile->Save ( NULL, FALSE );

    if ( FAILED(hr) )
        {
        fprintf(stderr, "Failed calling Save, error = 0x%x\n",hr);

        return hr;
        }
  
  /////////////////////////////////////////////////////////////////
  // Zwolnij zasoby
  /////////////////////////////////////////////////////////////////
  
  hr = pITask->Release();
  if (FAILED(hr))
  {
     CoUninitialize();
     fprintf(stderr, "Failed calling Release, error = 0x%x\n",hr);
     return 1;
  }
  
  
  printf("Succesfully created task and trigger.\n");


  return 0;
}
