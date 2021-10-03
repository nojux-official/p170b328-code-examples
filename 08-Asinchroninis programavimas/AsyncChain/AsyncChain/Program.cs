using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace AsyncChain
{
    internal static class Program
    {
        /// <summary>
        /// A program that queries current temperature of several different cities asynchronously and prints them to
        /// console
        /// </summary>
        private static async Task Main()
        {
            // weather is going to be retrieved from OpenWeather service. It is access using OpenWeatherAPI class
            var api = new OpenWeatherApi();
            // create a dictionary with keys being city IDs in OpenWeather services, values - city names
            var cities = new Dictionary<int, string>
            {
                {598098, "Klaipėda"},
                {593116, "Vilnius"},
                {596128, "Panevėžys"},
                {597231, "Marijampolė"},
                {598316, "Kaunas"},
            };
            var tasks = cities
                .Select(async cityData =>
                {
                    var (cityId, cityName) = cityData;
                    // get temperature asynchronously
                    var response = await api.GetTemperatureAsync(cityId);
                    return new Tuple<string, double>(cityName, response);
                })
                .ToList();
            // create a combined task so we can use it to wait for all combined tasks at once
            var responses = await Task.WhenAll(tasks);
            // when all tasks are finished, print the results
            foreach (var response in responses)
            {
                var (cityName, temperature) = response;
                Console.WriteLine($"{cityName}: {temperature:F2}");
            }
        }
    }
}