#pragma once

#ifndef __ODBCTESTFIXTURE_H__
#define __ODBCTESTFIXTURE_H__

class LocalFixture
{
public:
    std::wstring DataSource = L"Ajaworks";
    std::wstring DatabaseName = L"AjaworksDev";


    LocalFixture( )
    {
    }
    ~LocalFixture( )
    {
    }
};

#endif

