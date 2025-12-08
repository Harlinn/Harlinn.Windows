# A simple time series container library.

This library contains simple time series container implementations intended 
for use with the Harlinn.Hydrology.Net library. 

The timeseries containers are ordered lists of Value elements, sorted by time.

The `IrregularTimeSeries` and `RegularTimeSeries` classes share a common implementation
`TimeSeriesBase`, and they are nearly as fast as `List<Value>`, while ensuring that the 
time series remains sorted.

Features:
- Fairly fast
- Simple implementation
- When a timeseries, containing values for <em>t<sub>1</sub></em> and <em>t<sub>3</sub></em>, is 
  queried for a value at <em>t<sub>2</sub></em> between <em>t<sub>1</sub></em> and <em>t<sub>3</sub></em> the
  timeseries will synthesize an interpolated value for <em>t<sub>2</sub></em>.
 

