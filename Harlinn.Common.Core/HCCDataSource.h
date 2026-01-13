#pragma once
#ifndef HARLINN_COMMON_CORE_HCCDATASOURCE_H_
#define HARLINN_COMMON_CORE_HCCDATASOURCE_H_
/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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
