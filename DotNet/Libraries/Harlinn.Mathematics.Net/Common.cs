namespace Harlinn.Mathematics.Net
{
    public class Common
    {
        /// <summary>
        /// Determines the complementary error of x.
        /// </summary>
        /// <param name="x">argument value</param>
        /// <returns>
        /// The complementary error of x.
        /// </returns>
        public static double Erfc(double x)
        {
            // take abs so that we are always in positive quadrant.
            double tmp = Math.Abs(x); 
            double fun;

            if (tmp > 3.0)
            {
                double f1 = (1.0 - 1.0 / (2.0 * tmp * tmp)
                       + 3.0 / (4.0 * Math.Pow(tmp, 4))
                       - 5.0 / (6.0 * Math.Pow(tmp, 6)));
                fun = f1 * Math.Exp(-tmp * tmp) / (tmp * Math.Sqrt(Math.PI));
            }
            else
            {
                double tmp2 = 1.0 / (1.0 + (0.3275911 * tmp));
                // 5th order polynomial interpolation
                double tmp3 = 0.254829592 * tmp2
                  - (0.284496736 * tmp2 * tmp2)
                  + (1.421413741 * Math.Pow(tmp2, 3))
                  - (1.453152027 * Math.Pow(tmp2, 4))
                  + (1.061405429 * Math.Pow(tmp2, 5));
                fun = tmp3 * Math.Exp(-tmp * tmp);
            }
            if (tmp == x) 
            { 
                return fun; 
            }
            else 
            { 
                return (2 - fun); 
            }
        }

        /// <summary>
        /// Calculates the error function of passed value x
        /// </summary>
        /// <param name="x">argument value</param>
        /// <returns>
        /// the error function of x.
        /// </returns>
        public static double Erf(double x)
        { 
            return 1.0 - Erfc(x);
        }


        /// <summary>
        /// Returns the value of the lognormal distribution function f_x(x) for the specified value x
        /// </summary>
        /// <param name="x">Double whose lognormal probability distribution value is to be returned</param>
        /// <param name="mu">Mean of transformed function Y = ln(x)</param>
        /// <param name="sig">Standard deviation of transformed distribution Y = ln(x)</param>
        /// <returns>
        /// Lognormal probability distribution value at x
        /// </returns>
        public static double LogPdf(double x, double mu, double sig)
        {
            if (x <= 0) 
            { 
                return 0.0; 
            }
            return 1.0 / x / sig / Math.Sqrt(2.0 * Math.PI) * Math.Exp(-0.5 * (Math.Pow((Math.Log(x) - mu) / sig, 2)));
        }

        /// <summary>
        /// Returns Nth recursive approximation of Lambert W_{-1} function
        /// </summary>
        /// <param name="x"></param>
        /// <param name="N"></param>
        /// <returns></returns>
        public static double LambertN(double x, int N)
        {
            double sigma, tmp;
            sigma = Math.Pow(-2.0 - 2.0 * Math.Log(-x), 0.5);
            if (N <= 2) 
            { 
                tmp = -1.0 - 0.5 * sigma * sigma - sigma / (1.0 + sigma / 6.3); 
            }
            else 
            { 
                tmp = LambertN(x, N - 1);
            }
            return (1 + Math.Log(-x) - Math.Log(-tmp)) * tmp / (1 + tmp);
        }


        static readonly double[] gamma2_g = [
                        1.0, 0.5772156649015329, -0.6558780715202538,
                        -0.420026350340952e-1, 0.1665386113822915, -0.421977345555443e-1,
                        -0.9621971527877e-2,   0.7218943246663e-2, -0.11651675918591e-2,
                        -0.2152416741149e-3,   0.1280502823882e-3, -0.201348547807e-4,
                        -0.12504934821e-5,     0.1133027232e-5,    -0.2056338417e-6,
                        0.6116095e-8,         0.50020075e-8,      -0.11812746e-8,
                        0.1043427e-9,         0.77823e-11,        -0.36968e-11,
                        0.51e-12,            -0.206e-13,          -0.54e-14,
                        0.14e-14];

        /// <summary>
        /// Returns gamma function of argument x
        /// </summary>
        /// <param name="x">Argument whose gamma function will be determined</param>
        /// <returns>Gamma function of argument x</returns>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public static double Gamma2(double x)
        {
            int i, k, m;
            double ga = 0, gr, r = 0, z;

            if (x > 171.0) 
            {
                // This value is an overflow flag.
                return 0.0; 
            }
            if (x == (int)x)
            {
                if (x > 0.0)
                {
                    // use factorial
                    ga = 1.0;
                    for (i = 2; i < x; i++) 
                    { 
                        ga *= i; 
                    }
                }
                else
                {
                    ga = 0.0;
                    throw new ArgumentOutOfRangeException(nameof(x), "Gamma:integer values <= 0 not allowed");
                }
            }
            else
            {
                z = x;
                r = 1.0;
                var absX = Math.Abs(x);
                if (absX > 1.0)
                {
                    z = absX;
                    m = (int)(z);
                    r = 1.0;
                    for (k = 1; k <= m; k++) { r *= (z - k); }
                    z -= m;
                }
                gr = gamma2_g[24];
                for (k = 23; k >= 0; k--) 
                { 
                    gr = gr * z + gamma2_g[k]; 
                }
                ga = 1.0 / (gr * z);
                if (absX > 1.0)
                {
                    ga *= r;
                    if (x < 0.0) 
                    { 
                        ga = -Math.PI / (x * ga * Math.Sin(Math.PI * x)); 
                    }
                }
            }
            return ga;
        }


        /// <summary>
        /// Calculates value of incomplete gamma function  with parameter a for input x
        /// incomplete Gamma is g(x,a)=int_0^x of t^a-1 exp(-t) dt
        /// </summary>
        /// <param name="x">upper limit of integral</param>
        /// <param name="a">shape parameter</param>
        /// <returns>
        /// Incomplete gamma function g(x,a)
        /// </returns>
        public static double IncompleteGamma(double x, double a)
        {
            const int N = 100;
            if (x <= 0) 
            { 
                return 0.0; 
            }
            double num = 1;
            double sum = 0.0;
            double prod = 1.0;
            for (int n=0;n<N;n++)
            {
                if (n>0)
                {
                    num*=x;
                }
                prod*=(a+n);
                sum+=num/prod;
            }
            return sum * Math.Pow(x, a) * Math.Exp(-x);
        }


        /// <summary>
        /// Calculates value of Gamma distribution for argument x, with parameters alpha and beta
        /// gamma(x,a,b)=b^a/Gamma(a)*x^(a-1)*exp(-b*x)
        /// </summary>
        /// <param name="x">Argument x whose Gamma distribution value will be determined</param>
        /// <param name="alpha">shape parameter</param>
        /// <param name="beta">scale parameter</param>
        /// <returns>
        /// The value of the Gamma distribution for argument x
        /// </returns>
        public static double GammaDist(double x, double alpha, double beta)
        {
            double bx = beta * x;
            return Math.Pow(bx, alpha) / x / Gamma2(x) * Math.Exp(-bx);
        }

        /// <summary>
        /// Calculates cumulative two parameter cumulative gamma distribution
        /// </summary>
        /// <param name="t">
        /// time
        /// </param>
        /// <param name="alpha">shape parameter</param>
        /// <param name="beta">scaling parameter</param>
        /// <returns>integrated gamma distribution from 0..t</returns>
        public static double GammaCumDist(double t,  double alpha,double beta)
        {
            return IncompleteGamma(beta * t, alpha) / Gamma2(alpha);
        }

        /// <summary>
        /// Calculates cumulative triangular distribution
        /// </summary>
        /// <param name="t">argument of triangular distribution</param>
        /// <param name="tc">End of triangle</param>
        /// <param name="tp">Peak of triangle</param>
        /// <returns>
        /// Cumulative triangular distribution value for input t
        /// </returns>
        public static double TriCumDist(double t, double tc, double tp)
        {
            double b = 2.0 / tc;
            if (t<0.0)
            {
                return 0.0;
            }
            if (t<=tp)
            {
                double m = (b/tp);
                return 0.5* m* t* t;
            }
            else if (t <= tc)
            {
                double m = -b / (tc - tp);
                return tp / tc + b * (t - tp) + 0.5 * m * (t - tp) * (t - tp);
            }
            else
            {
                return 1.0;
            }
        }

        /// <summary>
        /// Returns the cumulative distribution function at input t for a sequence of linear reservoirs
        /// \remark Basically the Gamma distribution for integer shape parameters. A common unit hydrograph format \n
        ///  - \math \f$ PDF(t)/UH(t)=t^{N-1}k^{N}e^{-kt} \f$
        ///  - \math \f$ CDF(t)/cum UH(t)=1-e^{-kt}\sum_{n=0}^{N-1}t^n/n! \f$
        /// </summary>
        /// <param name="t">The input value whose CDF is to be determined</param>
        /// <param name="k">CDF Parameter (linear storage coeff)</param>
        /// <param name="NR">Integer number of reservoirs</param>
        /// <returns>CDF at point t</returns>
        public static double NashCumDist(double t, double k, int NR)
        {
            if (t<0.0)
            {
                return 0.0;
            }
            double fact = 1.0;
            double prod = 1.0;
            double sum = 1.0;
            for (int n=1; n<NR; n++)
            {
                fact=fact* n;
                prod=prod* (k* t);
                sum+=prod/fact;
            }
            return 1.0 - Math.Exp(-k * t) * sum;
        }

        /// <summary>
        /// Calculates cumulative kinematic wave solution distribution
        /// </summary>
        /// <param name="t">time [d]</param>
        /// <param name="L">reach length [m]</param>
        /// <param name="v">celerity [m/d]</param>
        /// <param name="D">diffusivity [m2/d]</param>
        /// <returns>Returns cumulative kinematic wave solution distribution</returns>
        public static double ADRCumDist(double t, double L, double v, double D)
        {
            double result = 0;
            if (t <= 0) 
            { 
                return 0.0; 
            }
            if (L < 500 * (D / v))
            {
                result = 0.5 * (Math.Exp((v * L) / D) * Erfc((L + v * t) / Math.Sqrt(4.0 * D * t)));
            }
            result += 0.5 * (Erfc((L - v * t) / Math.Sqrt(4.0 * D * t)));
            return result;
        }

        /// <summary>
        /// Calculates the time-varying cumulative kinematic wave solution distribution
        /// </summary>
        /// <param name="t">time [d]</param>
        /// <param name="L">reach length [m]</param>
        /// <param name="v">array of celerities [m/d]</param>
        /// <param name="D">diffusivity [m2/d]</param>
        /// <param name="dt">timestep [d]</param>
        /// <returns>
        /// The cumulative kinematic wave solution distribution for temporally variable velocity.
        /// </returns>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public static double TimeVaryingADRCumDist(double t, double L, double[] v, double D, double dt)
        {
            if(D <= 0)
            {
                throw new ArgumentOutOfRangeException(nameof(D), "Diffusivity must be greater than zero.");
            }
            if(t > v.Length * dt)
            {
                throw new ArgumentOutOfRangeException(nameof(t), "Not enough celerity terms in array.");
            }
            int i;
            i = (int)(Math.Floor((t + 0.0001) / dt));
            double tstar = v[i] / v[0] * (t - (double)(i) * dt);
            for (int j = 0; j < i; j++)
            {
                tstar += dt * v[j] / v[0];
            }
            double result = 0;
            if (t <= 0) 
            { 
                return 0.0; 
            }
            if (L < 500 * (D / v[0]))
            {
                result = 0.5 * (Math.Exp((v[0] * L) / D) * Erfc((L + v[0] * tstar) / Math.Sqrt(4.0 * D * tstar)));
            }
            result += 0.5 * (Erfc((L - v[0] * tstar) / Math.Sqrt(4.0 * D * tstar)));
            return result;
        }

        /// <summary>
        /// calculates N process weights from N-1 numbers ranging from 0 to 1
        /// </summary>
        /// <param name="aVals">
        /// array of weight seeds (uniform numbers) between 0 and 1 (size:N-1)
        /// </param>
        /// <param name="aWeights">array of weights between 0 and 1</param>
        public static void CalcWeightsFromUniformNums(double[] aVals, double[] aWeights)
        {
            int N = aWeights.Length;
            double sum = 0.0;
            for (int q = 0; q < (N - 1); q++) 
            {
                aWeights[q] = (1.0 - sum) * (1.0 - Math.Pow(1.0 - aVals[q], 1.0 / (N - q - 1)));
                sum += aWeights[q];
            }
            aWeights[N - 1] = 1.0 - sum;
        }

        static int SmartIntervalSearch(double x,double[] ax,int iguess)
        {
            int N = ax.Length;
            int i = iguess;
            if((iguess>N-1) || (iguess<0)) 
            { 
                i=0; 
            }
            if((x>=ax[i]) && (x<ax[i + 1])) 
            { 
                return i; 
            }

            int plus, plus2;
            for (int d = 1; d < ((N / 2) + 1); d++)
            {
                plus = i + d; if (plus > N - 1) 
                { 
                    plus -= N; 
                }
                plus2 = i + d + 1; 
                if (plus2 > N - 1) 
                { 
                    plus2 -= N; 
                }
                if ((x >= ax[plus]) && (x < ax[plus2])) 
                { 
                    return plus; 
                }
                plus = i - d; 
                if (plus < 0) 
                { 
                    plus += N; 
                }
                plus2 = i - d + 1; 
                if (plus2 < 0) 
                { 
                    plus2 += N; 
                }
                if ((x >= ax[plus]) && (x < ax[plus2])) 
                { 
                    return plus; 
                }
            }
            return -1;
        }

        // Smallest possible double value to be used
        const double REAL_SMALL = 1e-12;
        /// <summary>
        /// interpolates value from rating curve
        /// </summary>
        /// <param name="x">
        /// interpolation location
        /// </param>
        /// <param name="xx">
        /// array of vertices ordinates of interpolant
        /// </param>
        /// <param name="y">
        /// array of values corresponding to array points xx
        /// </param>
        /// <param name="extrapbottom">
        /// Does not assume regular spacing between min and max x value
        /// if below minimum xx, either extrapolates (if extrapbottom=true), or uses minimum value
        /// if above maximum xx, always extrapolates
        /// </param>
        /// <returns>
        /// y value corresponding to interpolation point
        /// </returns>
        public static double InterpolateCurve(double x,double[] xx, double[] y, bool extrapbottom)
        {
            int N = xx.Length;
            int ilast = 0;
            if(x<=xx[0])
            {
                if(extrapbottom) 
                { 
                    return y[0]+(y[1]-y[0])/(xx[1]-xx[0])*(x-xx[0]); 
                }
                return y[0];
            }
            else if (x >= xx[N - 1])
            {
                return y[N - 1] + (y[N - 1] - y[N - 2]) / (xx[N - 1] - xx[N - 2]) * (x - xx[N - 1]);
            }
            else
            {
                int i = SmartIntervalSearch(x, xx, ilast);
                if (i < 0) 
                { 
                    return 0.0; 
                }
                ilast = i;
                if (Math.Abs(xx[i + 1] - xx[i]) < REAL_SMALL) 
                { 
                    return (y[i] + y[i + 1]) / 2; 
                }
                return y[i] + (y[i + 1] - y[i]) / (xx[i + 1] - xx[i]) * (x - xx[i]);
            }
        }



}
}
