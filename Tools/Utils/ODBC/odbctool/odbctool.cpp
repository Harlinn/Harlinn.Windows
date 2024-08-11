#include "odbctool.h"


int main()
{
    using namespace Harlinn::ODBC::Tool;
    Harlinn::Common::Core::ComInitialize comInitializer;
    auto storageInfo = StorageInfo::LoadFromFile( L"TestStorage.xml" );
    
}

