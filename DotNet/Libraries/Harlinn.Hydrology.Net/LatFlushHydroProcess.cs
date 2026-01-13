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

using static Harlinn.Hydrology.Constants;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Calculates the complete dump of water from one storage compartment 
    /// in one HRU to another in another HRU
    /// </summary>
    public class LatFlushHydroProcess : LateralExchangeHydroProcess
    {
        /// <summary>
        /// global state variable index of source state var
        /// </summary>
        int _iFlushFrom;
        /// <summary>
        /// global state variable index of target state var
        /// </summary>
        int _iFlushTo;
        /// <summary>
        /// HRU group index of source HRUs
        /// </summary>
        int _kk_from;
        /// <summary>
        /// HRU group index of target HRUs
        /// </summary>
        int _kk_to;
        /// <summary>
        /// all transfer is within one sub-basin; otherwise, requires only one recipient HRU in model
        /// </summary>
        bool _constrain_to_SBs;

        public LatFlushHydroProcess(Model model, int from_sv_ind,
                         int to_sv_ind,
                         int from_HRU_grp,
                         int to_HRU_grp,
                         bool constrain_to_SBs)
            : base(model, HydroProcessType.LAT_FLUSH)
        {
            _iFlushFrom = from_sv_ind;
            _iFlushTo = to_sv_ind;
            _kk_from = from_HRU_grp;
            _kk_to = to_HRU_grp;
            _constrain_to_SBs = constrain_to_SBs;

            DynamicSpecifyConnections(0); //purely lateral flow, no vertical

            //check for valid SVs, HRU group indices
            bool badHRU = (to_HRU_grp < 0) || (to_HRU_grp > model.GetNumHRUGroups() - 1);
            if(badHRU)
            {
                throw new ArgumentException("LatFlushHydroProcess: unrecognized 'to' HRU group specified in :LateralFlush command");
            }

            badHRU = (from_HRU_grp < 0) || (from_HRU_grp > model.GetNumHRUGroups() - 1);
            if(badHRU)
            {
                throw new ArgumentException("LatFlushHydroProcess: unrecognized 'from' HRU group specified in :LateralFlush command");
            }
            if(from_sv_ind == DOESNT_EXIST)
            {
                throw new ArgumentException("LatFlushHydroProcess: unrecognized 'from' state variable specified in :LateralFlush command");
            }
            if(to_sv_ind == DOESNT_EXIST)
            {
                throw new ArgumentException("LatFlushHydroProcess: unrecognized 'to' state variable specified in :LateralFlush command");
            }
        }

        public override void Initialize()
        {
            int nConn;
            int[] kFrom = new int[Model.GetNumHRUs()];
            int[] kTo = new int[Model.GetNumHRUs()];
            string fromHRUGrp = Model.GetHRUGroup(_kk_from).GetName();
            string toHRUGrp = Model.GetHRUGroup(_kk_to).GetName();
            int q = 0;
            int k;

            if (_constrain_to_SBs)
            {
                //sift through all HRUs
                for (int p = 0; p < Model.GetNumSubBasins(); p++)
                {
                    //find 'to' HRU (only one allowed per SB)
                    int kToSB = DOESNT_EXIST;
                    for (int ks = 0; ks < Model.GetSubBasin(p)->GetNumHRUs(); ks++)
                    {
                        k = Model.GetSubBasin(p)->GetHRU(ks)->GetGlobalIndex();

                        if (Model.IsInHRUGroup(k, toHRUGrp))
                        {
                            ExitGracefullyIf(kToSB != DOESNT_EXIST,
                              "LatFlush::Initialize - only one HRU per subbasin can recieve flush output. More than one recipient HRU found in subbasin ", BAD_DATA_WARN);
                            kToSB = k;
                        }
                    }

                    //find 'from' HRUs to make connections
                    for (int ks = 0; ks < Model.GetSubBasin(p)->GetNumHRUs(); ks++)
                    {
                        k = Model.GetSubBasin(p)->GetHRU(ks)->GetGlobalIndex();

                        if (Model.IsInHRUGroup(k, fromHRUGrp) && (kToSB != DOESNT_EXIST))
                        {
                            kFrom[q] = k;
                            kTo[q] = kToSB;
                            q++;
                        }
                    }
                }
                nConn = q;
                if (nConn == 0)
                {
                    string warning = "CmvLatFlush::Initialize: no connections found between from and to HRU groups in any of the basins. if INTERBASIN flag not used, only transfer within basins is supported. ";
                    WriteWarning(warning, true);
                }
            }
            else //!constrain_to_SBs
            {
                //toHRUGrp
                int kToSB = DOESNT_EXIST;
                for (k = 0; k < Model.GetNumHRUs(); k++)
                {
                    if (Model.IsInHRUGroup(k, toHRUGrp))
                    {
                        ExitGracefullyIf(kToSB != DOESNT_EXIST,
                          "LatFlush::Initialize - only one HRU in the model can recieve flush output. More than one recipient HRU found.", BAD_DATA_WARN);
                        kToSB = k;
                    }
                }
                //find 'from' HRUs to make connections
                for (k = 0; k < Model.GetNumHRUs(); k++)
                {
                    if (Model.IsInHRUGroup(k, fromHRUGrp) && (kToSB != DOESNT_EXIST))
                    {
                        kFrom[q] = k;
                        kTo[q] = kToSB;
                        q++;
                    }
                }
                nConn = q;
                if (nConn == 0)
                {
                    string warning = "CmvLatFlush::Initialize: no connections found between from and to HRU groups. HRU Group population of zero?";
                    WriteWarning(warning, true);
                }
            }

            DynamicSpecifyLatConnections(nConn);
            for (q = 0; q < _nLatConnections; q++)
            {
                _kFrom[q] = kFrom[q];
                _kTo[q] = kTo[q];
                _iFromLat[q] = _iFlushFrom;
                _iToLat[q] = _iFlushTo;
                /*cout << "latflush connections: " << Model.GetHydroUnit(_kFrom[q])->GetID() << " " << Model.GetHydroUnit(_kTo[q])->GetID() << " ";
                cout<<Model.GetStateVarInfo()->SVTypeToString(Model.GetStateVarType(_iFromLat[q]),-1)<<" ";
                cout<<Model.GetStateVarInfo()->SVTypeToString(Model.GetStateVarType(_iToLat[q]),-1)<<endl;*/
            }
            delete[] kFrom;
            delete[] kTo;
        }

    }
}
