#pragma once
#ifndef HARLINN_COMMON_CORE_HCCDATASOURCE_H_
#define HARLINN_COMMON_CORE_HCCDATASOURCE_H_

#include <HCCObservable.h>
#include <HCCTraits.h>

namespace Harlinn::Common::Core
{
    class DataSourceColumn : public Observable<DataSourceColumn>
    {
    public:
        using Base = Observable<DataSourceColumn>;
        using ThisType = DataSourceColumn;
    private:
        int index_;
        Types::BasicTypeId typeId_;
    public:
        DataSourceColumn( ) = default;
        virtual ~DataSourceColumn( ) noexcept override = default;
    };


    class DataSource : public Observable<DataSource>
    {
    public:
        using Base = Observable<DataSource>;
        using ThisType = DataSource;
    private:
    public:
        DataSource( ) = default;
        virtual ~DataSource( ) noexcept override = default;



    };


}



#endif
