#pragma once

#ifndef __ODBCTESTFIXTURE_H__
#define __ODBCTESTFIXTURE_H__

class LocalFixture
{
public:
    using WideString = Harlinn::Common::Core::WideString;
    WideString DataSource = L"Ajaworks";
    WideString DatabaseName = L"AjaworksDev";


    LocalFixture( )
    {
    }
    ~LocalFixture( )
    {
    }
};

#endif

