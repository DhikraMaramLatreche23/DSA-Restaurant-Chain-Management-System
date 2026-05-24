#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>   // For time_t, tm, localtime
#include <cstdlib> // For std::time
#include <iomanip>
#include <chrono>
#include <stack>
#include <list>

// #include <cstdlib>

using namespace std;

// sales and costs
struct Sales
{
    int day;
    double Algerian_sales;
    double Indian_sales;
    double Chinese_sales;
    double Syrian_sales;
    double Europ_sales;

    Sales() : day(0), Algerian_sales(0.00), Indian_sales(0), Chinese_sales(0), Syrian_sales(0), Europ_sales(0) {}
};

struct MonthlySales
{
    int month;
    std::vector<Sales> days;

    double Algerian_sales;
    double Indian_sales;
    double Chinese_sales;
    double Syrian_sales;
    double Europ_sales;

    MonthlySales() : month(0), days(31), Algerian_sales(0), Indian_sales(0), Chinese_sales(0), Syrian_sales(0), Europ_sales(0) {}
};

struct YearlySales
{
    int year;
    std::vector<MonthlySales> months;
    double Algerian_sales;
    double Indian_sales;
    double Chinese_sales;
    double Syrian_sales;
    double Europ_sales;

    YearlySales() : year(0), months(12), Algerian_sales(0), Indian_sales(0), Chinese_sales(0), Syrian_sales(0), Europ_sales(0) {}
};
/**problem in ratio list for district */

class SalesRestaurant
{

private:
    std::vector<YearlySales> yearlyData;

public:
    SalesRestaurant(int yearsToTrack = 10) : yearlyData(yearsToTrack) {}
    // insert sales

    void recordSales(int year, int month, int day, double Algerian_sales, double Indian_sales, double Chinese_sales, double Syrian_sales, double Europ_sales)
    {

        if (!isValidDate(year, month, day))
        {
            std::cout << "Invalid date. Please enter a valid date (2000 - 2023 for year, 1 - 12 for month, 1 - 31 for day)." << std::endl;
            return;
        }

        YearlySales &currentYear = yearlyData[year - 2000];
        MonthlySales &currentMonth = currentYear.months[month - 1];
        Sales &currentDay = currentMonth.days[day - 1];
        initializeSalesValues(currentDay);
        updateDailySales(currentMonth, currentYear, currentDay, Algerian_sales, Indian_sales, Chinese_sales, Syrian_sales, Europ_sales);
        //  updateMonthlyAndYearlySales(currentMonth, currentYear, Algerian_sales, Indian_sales, Chinese_sales, Syrian_sales, Europ_sales);
    }

    double SalesOfDate(int year, int month, int day)
    {

        if (!isValidDate(year, month, day))
        {
            std::cout << "Invalid date." << std::endl;
        }

        const YearlySales &currentYear = yearlyData[year - 2000];
        const MonthlySales &currentMonth = currentYear.months[month - 1];
        const Sales &currentDay = currentMonth.days[day - 1];

        std::cout << "\n";
        std::cout << "Daily Sales for " << year << " / " << month << " / " << day << ":\n";
        std::cout << "--------------------------------\n";
        std::cout << "Cuisine\t\tSales\n";

        // Print individual cuisine sales for the day
        std::cout << "Algerian\t" << currentDay.Algerian_sales << std::endl;
        std::cout << "Syrian\t\t" << currentDay.Syrian_sales << std::endl;
        std::cout << "Indian\t\t" << currentDay.Indian_sales << std::endl;
        std::cout << "Chinese\t\t" << currentDay.Chinese_sales << std::endl;
        std::cout << "European\t" << currentDay.Europ_sales << std::endl;

        double totalSales = currentDay.Algerian_sales + currentDay.Indian_sales +
                            currentDay.Chinese_sales + currentDay.Syrian_sales +
                            currentDay.Europ_sales;

        std::cout << "The Total sales of the date is : " << year << "/" << month << "/" << day << " is : ";
        return totalSales;
    }

    double SalesOfMonth(int year, int month)
    {

        double totalSales = 0;

        if (isValidDate(year, month, 1))
        {
            const YearlySales &currentYear = yearlyData[year - 2000];

            if (month <= currentYear.months.size())
            {
                const MonthlySales &currentMonth = currentYear.months[month - 1];

                for (const auto &day : currentMonth.days)
                {
                    // Add the sales for all cuisines on this day
                    totalSales += day.Algerian_sales + day.Indian_sales + day.Chinese_sales + day.Syrian_sales + day.Europ_sales;
                }

                std::cout << "\n";
                std::cout << "Monthly Sales for " << year << " / " << month << ":\n";
                std::cout << "--------------------------------\n";
                std::cout << "Cuisine\t\tSales\n";
                std::cout << "\n";
                std::cout << "Algerian\t" << currentMonth.Algerian_sales << std::endl;
                std::cout << "Syrian\t\t" << currentMonth.Syrian_sales << std::endl;
                std::cout << "Indian\t\t" << currentMonth.Indian_sales << std::endl;
                std::cout << "Chinese\t\t" << currentMonth.Chinese_sales << std::endl;
                std::cout << "European\t" << currentMonth.Europ_sales << std::endl;

                std::cout << " The total sales for this month  " << year << " / " << month << " is :  ";
                return totalSales;
            }
            else
            {
                std::cout << "Invalid month. Please enter a valid month (1 - 12)." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid date. Please enter a valid date (2000 - 2023 for year, 1 - 12 for month)." << std::endl;
        }
    }

    double SalesOfMonthForRatioFun(int year, int month)
    {

        double totalSales = 0;

        if (isValidDate(year, month, 1))
        {
            const YearlySales &currentYear = yearlyData[year - 2000];

            if (month <= currentYear.months.size())
            {
                const MonthlySales &currentMonth = currentYear.months[month - 1];

                for (const auto &day : currentMonth.days)
                {
                    // Add the sales for all cuisines on this day
                    totalSales += day.Algerian_sales + day.Indian_sales + day.Chinese_sales + day.Syrian_sales + day.Europ_sales;
                }

                return totalSales;
            }
            else
            {
                std::cout << "Invalid month. Please enter a valid month (1 - 12)." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid date. Please enter a valid date (2000 - 2023 for year, 1 - 12 for month)." << std::endl;
        }
    }
    double SalesOfYear(int year)
    {
        if (isValidDate(year, 1, 1))
        {

            double totalSales = 0;
            const YearlySales &currentYear = yearlyData[year - 2000];

            for (const auto &month : currentYear.months)
            {
                // Add the sales for all cuisines in this month
                totalSales += month.Algerian_sales + month.Indian_sales + month.Chinese_sales + month.Syrian_sales + month.Europ_sales;
            }
            std::cout << "Yearly Sales for " << year << ":\n";
            std::cout << "--------------------------------\n";
            std::cout << "Cuisine\t\tSales\n";

            std::cout << "Algerian\t" << currentYear.Algerian_sales << std::endl;
            std::cout << "Syrian\t\t" << currentYear.Syrian_sales << std::endl;
            std::cout << "Indian\t\t" << currentYear.Indian_sales << std::endl;
            std::cout << "Chinese\t\t" << currentYear.Chinese_sales << std::endl;
            std::cout << "European\t" << currentYear.Europ_sales << std::endl;

            std::cout << "The total sales of year " << year << " is ";
            return totalSales;
        }

        else
        {
            std::cout << "Invalid date. Please enter a valid year (2000 - 2023)." << std::endl;
        }
    }

    double TotalSalesBetweenDates(int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay)
    {

        if (!isValidDate(startYear, startMonth, startDay) || !isValidDate(endYear, endMonth, endDay))
        {
            std::cout << "Invalid dates. Please enter valid dates." << std::endl;
        }

        double totalSales = 0;

        for (int year = startYear; year <= endYear; ++year)
        {
            const YearlySales &currentYear = yearlyData[year - 2000];

            for (int month = 1; month <= 12; ++month)
            {
                if ((year == startYear && month < startMonth) || (year == endYear && month > endMonth))
                {
                    // Skip months before startMonth in startYear and after endMonth in endYear
                    continue;
                }

                const MonthlySales &currentMonth = currentYear.months[month - 1];

                for (int day = 1; day <= 31; ++day)
                {
                    if ((year == startYear && month == startMonth && day < startDay) ||
                            (year == endYear && month == endMonth && day > endDay))
                    {
                        // Skip days before startDay in startMonth/startYear and after endDay in endMonth/endYear
                        continue;
                    }

                    const Sales &currentDay = currentMonth.days[day - 1];

                    // Add the sales for all cuisines on this day
                    totalSales += currentDay.Algerian_sales + currentDay.Indian_sales +
                                  currentDay.Chinese_sales + currentDay.Syrian_sales + currentDay.Europ_sales;
                }
            }
        }
        cout << " The total Sales from " << startYear << "/" << startMonth << "/" << startDay << " to " << endYear << "/" << endMonth << "/" << endDay << " is : ";

        return totalSales;
    }

    double displayDailySalesForCuisine(int year, int month, int day, const std::string &cuisine) const
    {
        if (isValidDate(year, month, day))
        {
            const YearlySales &currentYear = yearlyData[year - 2000];
            const MonthlySales &currentMonth = currentYear.months[month - 1];
            const Sales &currentDay = currentMonth.days[day - 1];

            // Transform cuisine to lowercase
            std::string lowercaseCuisine = cuisine;
            transform(lowercaseCuisine.begin(), lowercaseCuisine.end(), lowercaseCuisine.begin(), ::tolower);

            // Output header information
            std::cout << "Daily sales for on " << year << "/" << month << "/" << day << " Cuisine " << cuisine << "\n";
            std::cout << "--------------------------------\n";

            // Use a variable to store the sales value
            double sales = 0.0;

            // Update the sales variable based on the cuisine
            if (lowercaseCuisine == "algerian")
            {
                sales = currentDay.Algerian_sales;
            }
            else if (lowercaseCuisine == "syrian")
            {
                sales = currentDay.Syrian_sales;
            }
            else if (lowercaseCuisine == "indian")
            {
                sales = currentDay.Indian_sales;
            }
            else if (lowercaseCuisine == "chinese")
            {
                sales = currentDay.Chinese_sales;
            }
            else if (lowercaseCuisine == "european")
            {
                sales = currentDay.Europ_sales;
            }
            else
            {
                // Handle invalid cuisine
                std::cout << "Invalid cuisine name!" << std::endl;
                return 0.0; // or another appropriate value
            }

            return sales;
        }
        else
        {
            std::cout << "INVALID DATE!" << std::endl;
            //       return 0.0; // or another appropriate value
        }
    }

    double displayMonthlySalesForCuisine(int year, int month, const std::string &cuisine)
    {
        if (isValidDate(year, month, 1))
        {
            const YearlySales &currentYear = yearlyData[year - 2000];

            // Check if the specified month is within the valid range
            if (month <= currentYear.months.size())
            {
                const MonthlySales &currentMonth = currentYear.months[month - 1];

                // Transform cuisine to lowercase
                std::string lowercaseCuisine = cuisine;
                transform(lowercaseCuisine.begin(), lowercaseCuisine.end(), lowercaseCuisine.begin(), ::tolower);

                // Use a variable to store the sales value
                double sales = 0.00;

                // Update the sales variable based on the cuisine
                if (lowercaseCuisine == "algerian")
                {
                    sales = currentMonth.Algerian_sales;
                }
                else if (lowercaseCuisine == "syrian")
                {
                    sales = currentMonth.Syrian_sales;
                }
                else if (lowercaseCuisine == "indian")
                {
                    sales = currentMonth.Indian_sales;
                }
                else if (lowercaseCuisine == "chinese")
                {
                    sales = currentMonth.Chinese_sales;
                }
                else if (lowercaseCuisine == "european")
                {
                    sales = currentMonth.Europ_sales;
                }
                else
                {
                    // Handle invalid cuisine
                    std::cout << "Invalid cuisine name!" << std::endl;
                    //     return 0.0; // or another appropriate value
                }

                // Output the sales value
                return sales;
            }
            else
            {
                std::cout << "Invalid month!" << std::endl;
                //  return 0.0; // or another appropriate value
            }
        }
        else
        {
            std::cout << "INVALID DATE!" << std::endl;
            //  return 0.0; // or another appropriate value
        }
    }

    double displayYearlySalesForCuisine(int year, const std::string &cuisine) const
    {
        if (isValidDate(year, 1, 1))
        {
            const YearlySales &currentYear = yearlyData[year - 2000];

            // Transform cuisine to lowercase
            std::string lowercaseCuisine = cuisine;
            transform(lowercaseCuisine.begin(), lowercaseCuisine.end(), lowercaseCuisine.begin(), ::tolower);

            // Output header information
            std::cout << "Yearly sales for in " << year << " Cuisine " << cuisine << "\n";
            std::cout << "--------------------------------\n";

            // Use a variable to store the sales value
            double sales = 0.0;

            // Update the sales variable based on the cuisine
            if (lowercaseCuisine == "algerian")
            {
                sales = currentYear.Algerian_sales;
            }
            else if (lowercaseCuisine == "syrian")
            {
                sales = currentYear.Syrian_sales;
            }
            else if (lowercaseCuisine == "indian")
            {
                sales = currentYear.Indian_sales;
            }
            else if (lowercaseCuisine == "chinese")
            {
                sales = currentYear.Chinese_sales;
            }
            else if (lowercaseCuisine == "european")
            {
                sales = currentYear.Europ_sales;
            }
            else
            {
                // Handle invalid cuisine
                std::cout << "Invalid cuisine name!" << std::endl;
                return 0.0; // or another appropriate value
            }

            // Output the sales value

            return sales;
        }
        else
        {
            std::cout << "INVALID DATE!" << std::endl;
            return 0.0; // or another appropriate value
        }
    }

    double displaySalesForCuisineInPERIOD(int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay, const std::string &cuisine) const
    {
        if (!isValidDate(startYear, startMonth, startDay) || !isValidDate(endYear, endMonth, endDay))
        {
            std::cout << "Invalid dates. Please enter valid dates." << std::endl;
            return 0;
        }
        else
        {
            double totalsales = 0.0;

            // Loop through the years, months, and days to calculate the total cost
            for (int year = startYear; year <= endYear; ++year)
            {
                const YearlySales &currentYear = yearlyData[year - 2000];

                for (int month = 1; month <= 12; ++month)
                {
                    if ((year == startYear && month < startMonth) || (year == endYear && month > endMonth))
                    {
                        // Skip months before startMonth in startYear and after endMonth in endYear
                        continue;
                    }

                    const MonthlySales &currentMonth = currentYear.months[month - 1];

                    for (int day = 1; day <= 31; ++day)
                    {
                        if ((year == startYear && month == startMonth && day < startDay) || (year == endYear && month == endMonth && day > endDay))
                        {
                            // Skip days before startDay in startMonth/startYear and after endDay in endMonth/endYear
                            continue;
                        }

                        const Sales &currentDay = currentMonth.days[day - 1];

                        std::string lowercaseCuisine = cuisine;
                        transform(lowercaseCuisine.begin(), lowercaseCuisine.end(), lowercaseCuisine.begin(), ::tolower);

                        if (lowercaseCuisine == "algerian")
                        {
                            totalsales += currentDay.Algerian_sales;
                        }
                        else if (lowercaseCuisine == "syrian")
                        {
                            totalsales += currentDay.Syrian_sales;
                        }
                        else if (lowercaseCuisine == "indian")
                        {
                            totalsales += currentDay.Indian_sales;
                        }
                        else if (lowercaseCuisine == "chinese")
                        {
                            totalsales += currentDay.Chinese_sales;
                        }
                        else if (lowercaseCuisine == "european")
                        {
                            totalsales += currentDay.Europ_sales;
                        }
                        else
                        {

                            std::cout << "Invalid cuisine name!" << std::endl;
                            return 0.0;
                        }
                    }
                }
            }

            std::cout << "Total Sales from " << startYear << "/" << startMonth << "/" << startDay << " to " << endYear << "/" << endMonth << "/" << endDay << " for cuisine " << cuisine << " is : ";
            return totalsales;
        }
    }

    void updateDailySales(MonthlySales &monthSales, YearlySales &yearSales, Sales &daySales, double Algerian, double Indian, double Chinese, double Syrian, double Europ)
    {
        daySales.Algerian_sales += Algerian;
        daySales.Indian_sales += Indian;
        daySales.Chinese_sales += Chinese;
        daySales.Syrian_sales += Syrian;
        daySales.Europ_sales += Europ;

        updateMonthlyAndYearlySales(monthSales, yearSales, Algerian, Indian, Chinese, Syrian, Europ);
    }

private:
    bool isValidDate(int year, int month, int day) const
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);
        int currentYear = now->tm_year + 1900;

        // Define the minimum and maximum valid years based on the CSV data
        const int minValidYear = 2000;
        const int maxValidYear = currentYear;

        return year >= minValidYear && year <= maxValidYear && month >= 1 && month <= 12 && day >= 1 && day <= 31;
    }

    void initializeSalesValues(Sales &sales) const
    {
        if (sales.Algerian_sales == 0 && sales.Indian_sales == 0 && sales.Chinese_sales == 0 && sales.Syrian_sales == 0 && sales.Europ_sales == 0)
        {
            sales.Algerian_sales = 0;
            sales.Indian_sales = 0;
            sales.Chinese_sales = 0;
            sales.Syrian_sales = 0;
            sales.Europ_sales = 0;
        }
    }

    void updateMonthlyAndYearlySales(MonthlySales &monthSales, YearlySales &yearSales, double Algerian, double Indian, double Chinese, double Syrian, double Europ)
    {
        monthSales.Algerian_sales += Algerian;
        monthSales.Indian_sales += Indian;
        monthSales.Chinese_sales += Chinese;
        monthSales.Syrian_sales += Syrian;
        monthSales.Europ_sales += Europ;

        yearSales.Algerian_sales += Algerian;
        yearSales.Indian_sales += Indian;
        yearSales.Chinese_sales += Chinese;
        yearSales.Syrian_sales += Syrian;
        yearSales.Europ_sales += Europ;
    }
};

struct DailyCosts
{
    double rent;
    double employees;
    double electricity;
    double gas;
    double vegetables;
    double meats;
    double otherIngredients;
    double publicity;
    double other;

    DailyCosts() : rent(0), employees(0), electricity(0), gas(0), vegetables(0), meats(0), otherIngredients(0), publicity(0), other(0) {}
};

struct MonthlyCosts
{
    int month;
    std::vector<DailyCosts> days;
    double rent;
    double employees;
    double electricity;
    double gas;
    double vegetables;
    double meats;
    double otherIngredients;
    double publicity;
    double other;

    MonthlyCosts() : month(0), days(31), rent(0), employees(0), electricity(0), gas(0), vegetables(0), meats(0), otherIngredients(0), publicity(0), other(0) {}
};

struct YearlyCosts
{
    int year;
    std::vector<MonthlyCosts> months;
    double rent;
    double employees;
    double electricity;
    double gas;
    double vegetables;
    double meats;
    double otherIngredients;
    double publicity;
    double other;

    YearlyCosts() : year(0), months(12), rent(0), employees(0), electricity(0), gas(0), vegetables(0), meats(0), otherIngredients(0), publicity(0), other(0) {}
};

class CostsRestaurant
{
private:
    std::vector<YearlyCosts> yearlyData;

public:
    CostsRestaurant(int yearsToTrack = 10) : yearlyData(yearsToTrack) {}

    // Function to record daily costs

    void recordCost(int year, int month, int day, double rent, double employees, double electricity, double gas, double vegetables, double meats, double otherIngredients, double publicity, double other)
    {

        if (!isValidDate(year, month, day))
        {
            std::cout << "Invalid date. Please enter a valid date (2000 - 2023 for year, 1 - 12 for month, 1 - 31 for day)." << std::endl;
            return;
        }

        YearlyCosts &currentYear = yearlyData[year - 2000];
        MonthlyCosts &currentMonth = currentYear.months[month - 1];
        DailyCosts &currentDay = currentMonth.days[day - 1];

        initializeCostValues(currentDay);

        updateDailyCost(currentMonth, currentYear, currentDay, rent, employees, electricity, gas, vegetables, meats, otherIngredients, publicity, other);
        //   updateMonthlyAndYearlyCosts(currentMonth, currentYear, rent, employees, electricity, gas, vegetables, meats, otherIngredients, publicity, other);
    }

    // Function to display total costs for a specific date
    double TotalCostDate(int year, int month, int day)
    {

        double totalCost = 0.0;

        // Check if the date is valid
        if (!isValidDate(year, month, day))
        {
            std::cout << "Invalid date." << std::endl;
            return 0;
        }

        // Access the structures and calculate the total cost
        const YearlyCosts &currentYear = yearlyData[year - 2000];
        const MonthlyCosts &currentMonth = currentYear.months[month - 1];
        const DailyCosts &currentDay = currentMonth.days[day - 1];

        std::cout << "\n";
        std::cout << "Daily Costs for " << year << "/" << month << "/" << day << ":\n";
        std::cout << "--------------------------------\n";
        std::cout << "Cost Item\t\tAmount\n";

        // Print individual cost items for the day
        std::cout << "Rent\t\t\t" << currentDay.rent << std::endl;
        std::cout << "Employees\t\t" << currentDay.employees << std::endl;
        std::cout << "Electricity\t\t" << currentDay.electricity << std::endl;
        std::cout << "Gas\t\t\t" << currentDay.gas << std::endl;
        std::cout << "Vegetables\t\t" << currentDay.vegetables << std::endl;
        std::cout << "Meats\t\t\t" << currentDay.meats << std::endl;
        std::cout << "Other Ingredients\t" << currentDay.otherIngredients << std::endl;
        std::cout << "Publicity\t\t" << currentDay.publicity << std::endl;
        std::cout << "Other\t\t\t" << currentDay.other << std::endl;

        // Calculate and print total cost for the day
        totalCost = currentDay.rent + currentDay.employees + currentDay.electricity + currentDay.gas +
                    currentDay.vegetables + currentDay.meats + currentDay.otherIngredients +
                    currentDay.publicity + currentDay.other;

        std::cout << "--------------------------------\n";
        std::cout << "Total Cost\t\t";
        return totalCost;
    }

    // Function to display total costs for a specific month
    double TotalCostMonth(int year, int month)
    {
        double totalCost = 0;

        // Check if the date is valid
        if (isValidDate(year, month, 1))
        {
            const YearlyCosts &currentYear = yearlyData[year - 2000];

            if (month <= currentYear.months.size())
            {
                const MonthlyCosts &currentMonth = currentYear.months[month - 1];

                std::cout << "\n";
                std::cout << "Monthly Costs for " << year << " / " << month << ":\n";
                std::cout << "--------------------------------\n";
                std::cout << "Cost Item\t\tAmount\n";

                // Print individual cost items for the month
                std::cout << "Rent\t\t\t" << currentMonth.rent << std::endl;
                std::cout << "Employees\t\t" << currentMonth.employees << std::endl;
                std::cout << "Electricity\t\t" << currentMonth.electricity << std::endl;
                std::cout << "Gas\t\t\t" << currentMonth.gas << std::endl;
                std::cout << "Vegetables\t\t" << currentMonth.vegetables << std::endl;
                std::cout << "Meats\t\t\t" << currentMonth.meats << std::endl;
                std::cout << "Other Ingredients\t" << currentMonth.otherIngredients << std::endl;
                std::cout << "Publicity\t\t" << currentMonth.publicity << std::endl;
                std::cout << "Other\t\t\t" << currentMonth.other << std::endl;

                // Calculate and print total cost for the month
                totalCost = currentMonth.rent + currentMonth.employees + currentMonth.electricity + currentMonth.gas +
                            currentMonth.vegetables + currentMonth.meats + currentMonth.otherIngredients +
                            currentMonth.publicity + currentMonth.other;

                std::cout << "--------------------------------\n";
                std::cout << "Total Cost\t\t";
                return totalCost;
                cout << endl;
            }
            else
            {
                std::cout << "Invalid month. Please enter a valid month (1 - 12)." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid date. Please enter a valid date (2000 - 2023 for year, 1 - 12 for month)." << std::endl;
        }
    }

    double TotalCostYear(int year)
    {
        double totalCost = 0;

        // Check if the date is valid
        if (isValidDate(year, 1, 1))
        {
            const YearlyCosts &currentYear = yearlyData[year - 2000];

            std::cout << "\n";
            std::cout << "Yearly Costs for " << year << ":\n";
            std::cout << "--------------------------------\n";
            std::cout << "Cost Item\t\tAmount\n";

            // Print individual cost items for the year
            std::cout << "Rent\t\t\t" << currentYear.rent << std::endl;
            std::cout << "Employees\t\t" << currentYear.employees << std::endl;
            std::cout << "Electricity\t\t" << currentYear.electricity << std::endl;
            std::cout << "Gas\t\t\t" << currentYear.gas << std::endl;
            std::cout << "Vegetables\t\t" << currentYear.vegetables << std::endl;
            std::cout << "Meats\t\t\t" << currentYear.meats << std::endl;
            std::cout << "Other Ingredients\t" << currentYear.otherIngredients << std::endl;
            std::cout << "Publicity\t\t" << currentYear.publicity << std::endl;
            std::cout << "Other\t\t\t" << currentYear.other << std::endl;

            // Calculate and print total cost for the year
            totalCost = currentYear.rent + currentYear.employees + currentYear.electricity + currentYear.gas +
                        currentYear.vegetables + currentYear.meats + currentYear.otherIngredients +
                        currentYear.publicity + currentYear.other;

            std::cout << "--------------------------------\n";
            std::cout << "Total Cost\t\t";
            return totalCost;
            std::cout << "\n";
        }
        else
        {
            std::cout << "Invalid date. Please enter a valid year (2000 - 2023)." << std::endl;
        }
    }

    // Function to display total costs between two dates
    double TotalCostBetweenDates(int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay)
    {
        if (!isValidDate(startYear, startMonth, startDay) || !isValidDate(endYear, endMonth, endDay))
        {
            std::cout << "Invalid dates. Please enter valid dates." << std::endl;
            return 0;
        }
        else
        {

            double totalCost = 0;

            // Loop through the years, months, and days to calculate the total cost
            for (int year = startYear; year <= endYear; ++year)
            {
                const YearlyCosts &currentYear = yearlyData[year - 2000];

                for (int month = 1; month <= 12; ++month)
                {
                    if ((year == startYear && month < startMonth) || (year == endYear && month > endMonth))
                    {
                        // Skip months before startMonth in startYear and after endMonth in endYear
                        continue;
                    }

                    const MonthlyCosts &currentMonth = currentYear.months[month - 1];

                    for (int day = 1; day <= 31; ++day)
                    {
                        if ((year == startYear && month == startMonth && day < startDay) || (year == endYear && month == endMonth && day > endDay))
                        {
                            // Skip days before startDay in startMonth/startYear and after endDay in endMonth/endYear
                            continue;
                        }

                        const DailyCosts &currentDay = currentMonth.days[day - 1];

                        // Add the costs for all items on this day
                        totalCost += currentDay.rent + currentDay.employees + currentDay.electricity + currentDay.gas + currentDay.vegetables + currentDay.meats + currentDay.otherIngredients + currentDay.publicity + currentDay.other;
                    }
                }
            }

            std::cout << "Total Costs "
                      << " from " << startYear << "/" << startMonth << "/" << startDay << " to " << endYear << "/" << endMonth << "/" << endDay << ": ";

            return totalCost;
            cout << endl;
        }
    }

    double caluclatePublicityCost(int year, int month) const
    {
        if (!isValidDate(year, month, 1))
        {
            return 0;
        }
        else
        {
            const YearlyCosts &currentYear = yearlyData[year - 2000];
            const MonthlyCosts &currentMonth = currentYear.months[month - 1];
            double publicitycost = currentMonth.publicity;

            return publicitycost;
        }
    }

    // Function to update daily costs
    void updateDailyCost(MonthlyCosts &monthCosts, YearlyCosts &yearCosts, DailyCosts &dayCosts, double rent, double employees, double electricity, double gas, double vegetables, double meats, double otherIngredients, double publicity, double other) const
    {
        dayCosts.rent += rent;
        dayCosts.employees += employees;
        dayCosts.electricity += electricity;
        dayCosts.gas += gas;
        dayCosts.vegetables += vegetables;
        dayCosts.meats += meats;
        dayCosts.otherIngredients += otherIngredients;
        dayCosts.publicity += publicity;
        dayCosts.other += other;

        updateMonthlyAndYearlyCosts(monthCosts, yearCosts, rent, employees, electricity, gas, vegetables, meats, otherIngredients, publicity, other);
    }

private:
    bool isValidDate(int year, int month, int day) const
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);
        int currentYear = now->tm_year + 1900;

        // Define the minimum and maximum valid years based on the CSV data
        const int minValidYear = 2000;
        const int maxValidYear = currentYear;

        return year >= minValidYear && year <= maxValidYear && month >= 1 && month <= 12 && day >= 1 && day <= 31;
    }

    // Function to initialize cost values if necessary
    void initializeCostValues(DailyCosts &costs) const
    {
        if (costs.rent == 0 && costs.employees == 0 && costs.electricity == 0 && costs.gas == 0 && costs.vegetables == 0 && costs.meats == 0 && costs.otherIngredients == 0 && costs.publicity == 0 && costs.other == 0)
        {
            costs.rent = 0;
            costs.employees = 0;
            costs.electricity = 0;
            costs.gas = 0;
            costs.vegetables = 0;
            costs.meats = 0;
            costs.otherIngredients = 0;
            costs.publicity = 0;
            costs.other = 0;
        }
    }

    // Function to update monthly and yearly costs
    void updateMonthlyAndYearlyCosts(MonthlyCosts &monthCosts, YearlyCosts &yearCosts, double rent, double employees, double electricity, double gas, double vegetables, double meats, double otherIngredients, double publicity, double other) const
    {
        monthCosts.rent += rent;
        monthCosts.employees += employees;
        monthCosts.electricity += electricity;
        monthCosts.gas += gas;
        monthCosts.vegetables += vegetables;
        monthCosts.meats += meats;
        monthCosts.otherIngredients += otherIngredients;
        monthCosts.publicity += publicity;
        monthCosts.other += other;

        yearCosts.rent += rent;
        yearCosts.employees += employees;
        yearCosts.electricity += electricity;
        yearCosts.gas += gas;
        yearCosts.vegetables += vegetables;
        yearCosts.meats += meats;
        yearCosts.otherIngredients += otherIngredients;
        yearCosts.publicity += publicity;
        yearCosts.other += other;
    }
};

class LinkFile
{
private:
    int id[4];

public:
    int asciiOfMyString(const string &str)
    {
        unsigned asciiCode = 0;
        for (char sh : str)
        {
            asciiCode = asciiCode * 37 + static_cast<int>(tolower(sh));
        }
        return asciiCode % 997;
        // return (asciiCode % 90) + 10;
    }
    int asciiOfMyCity(const string &str)
    {
        unsigned asciiCode = 0;
        for (char sh : str)
            asciiCode = (asciiCode * 37 + static_cast<int>(tolower(sh))) % 10007;
        return asciiCode % 997;
    }

    long long generateID(string wilaya, string district, string city)
    {
        static int autoIncr = 0;
        id[0] = asciiOfMyString(wilaya);
        id[1] = asciiOfMyString(district);
        id[2] = asciiOfMyCity(city);
        id[3] = autoIncr++;

        long long result = id[0] * 1000000000LL + id[1] * 1000000LL + id[2] * 1000LL + id[3];

        return result;
    }

    void addId(string &line)
    {
        stringstream ss(line);

        string restaurantName, ownership, numEmployees, wilaya, district, city, establishmentDate, id;
        getline(ss, restaurantName, ',');
        getline(ss, ownership, ',');
        getline(ss, numEmployees, ',');
        getline(ss, wilaya, ',');
        getline(ss, district, ',');
        getline(ss, city, ',');
        getline(ss, establishmentDate, ',');
        getline(ss, id);

        if (id.empty()) // Check if the line does not already have an ID
        {
            long long value = generateID(wilaya, district, city);

            stringstream idStream;
            idStream << value;
            line += "," + idStream.str();
        }
    }

    void readId()
    {
        ifstream infile("dba.csv");
        ofstream tempfile("temp.csv");

        if (infile.is_open() && tempfile.is_open())
        {
            string line;
            while (getline(infile, line))
            {
                addId(line);
                tempfile << line << endl; // Write the modified line to tempfile
            }

            infile.close();
            tempfile.close();

            remove("dba.csv");
            rename("temp.csv", "dba.csv");
        }
    }
    long long updateId()
    {
        ifstream infile("dba.csv");

        if (!infile.is_open())
        {
            cerr << "Error: Unable to open file." << endl;
            return -1;
        }

        string line;
        long long variable = -1; // Default value

        // Read lines until the end of the file
        while (getline(infile, line))
        {
            stringstream ss(line);

            string restaurantName, ownership, numEmployees, wilaya, district, city, establishmentDate, id;
            getline(ss, restaurantName, ',');
            getline(ss, ownership, ',');
            getline(ss, numEmployees, ',');
            getline(ss, wilaya, ',');
            getline(ss, district, ',');
            getline(ss, city, ',');
            getline(ss, establishmentDate, ',');
            getline(ss, id);

            if (!id.empty())
            {
                try
                {
                    variable = stoll(id);
                }
                catch (const invalid_argument &e)
                {
                    cerr << "Error: Invalid argument for conversion to long long." << endl;
                    variable = -1;
                }
            }
        }

        infile.close(); // Close the file

        return variable;
    }
};

// cuisine
struct cuisine
{
    string type;
    double cuisine_sales; // per day

    cuisine(string t, double s) : type(t), cuisine_sales(s) {}
};

// resturant

class RestaurantChainManagementSystem
{

private:
    struct Restaurant
    {
        string name;
        long long id;
        int numEmployees;
        string ownership;

        Restaurant *left;
        Restaurant *right;

        SalesRestaurant sales;
        CostsRestaurant cost;

        cuisine The_five_cuisines[5] =
        {
            {"Algerian", 0}, {"Syrian", 0}, {"Chinese", 0}, {"Indian", 0}, {"European", 0}
        };

        // Constructor to initialize the values
        Restaurant(string _name, long long _id, string _owner, int _numEmployees, Restaurant *l, Restaurant *r, SalesRestaurant s, CostsRestaurant c)
            : name(_name), id(_id), numEmployees(_numEmployees), ownership(_owner), left(l), right(r), sales(s), cost(c)
        {

            //   LinkFile object;
            //  id = object.updateId();
        }
    };

    Restaurant *root;

    Restaurant *clone(Restaurant *rhs) const
    {
        if (rhs == nullptr)
        {
            return nullptr;
        }
        else
        {
            return new Restaurant(rhs->name, rhs->id, rhs->ownership, rhs->numEmployees, clone(rhs->left), clone(rhs->right), rhs->sales, rhs->cost);
        }
    }

    void clear(Restaurant *t)
    {
        if (t)
        {
            clear(t->left);
            clear(t->right);

            delete t;
        }
    }

    void insert(Restaurant *&root, Restaurant *t)
    {
        if (root == nullptr)
        {
            root = t;
        }
        else if (t->id < root->id)
            insert(root->left, t);
        else if (t->id > root->id)
            insert(root->right, t);
        else
        {
        };
        //   std::cout << "Added restaurant: " << t->name << ", ID: " << t->id<<endl;
    }

    Restaurant *removeRestaurant(Restaurant *root, long long id)
    {
        if (root == nullptr)
            return root;
        if (id < root->id)
        {
            root->left = removeRestaurant(root->left, id);
        }
        else if (id > root->id)
        {
            root->right = removeRestaurant(root->right, id);
        }
        else
        {
            if (root->left == nullptr)
            {
                Restaurant *temp = root->right;
                delete root;
                return temp;
            }

            else if (root->right == nullptr)
            {
                Restaurant *temp = root->left;
                delete root;
                return temp;
            }
            Restaurant *temp = findMin(root->right);
            root->id = temp->id;
            root->right = removeRestaurant(root->right, temp->id);
        }
        return root;
    }

    Restaurant *findMin(Restaurant *node) const
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // Function to determine the prize-winning cuisine for a restaurant in a given month

    Restaurant *determineWinnersHelper(Restaurant *root, int month, int year, const std::string &type, std::stack<Restaurant *> &Winners)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        double rootAmount = calculateAmount(root, year, month, type);

        // Update the top restaurant in the stack if needed
        if (Winners.empty() || rootAmount > calculateAmount(Winners.top(), year, month, type))
        {
            Winners = std::stack<Restaurant *>(); // Clear the stack
            Winners.push(root);
        }

        // Determine winners in the left and right subtrees
        determineWinnersHelper(root->left, month, year, type, Winners);
        determineWinnersHelper(root->right, month, year, type, Winners);

        return Winners.empty() ? nullptr : Winners.top();
    }

    Restaurant *determineWinners(Restaurant *root, int month, int year, const std::string &type)
    {
        std::stack<Restaurant *> Winners;

        return determineWinnersHelper(root, month, year, type, Winners);
    }

    double Caluclate_ratio(SalesRestaurant &sales, CostsRestaurant &cost, int year, int month)
    {
        if (sales.SalesOfMonthForRatioFun(year, month) != 0)
        {
            return (cost.caluclatePublicityCost(year, month) / sales.SalesOfMonthForRatioFun(year, month));
        }
        else
            cout << "  ";
    }

    /* Private search*/
    int asciiOfMyString(const string &str)
    {
        unsigned asciiCode = 0;
        for (char sh : str)
        {
            asciiCode = asciiCode * 37 + static_cast<int>(tolower(sh));
        }
        return asciiCode % 997;
        // return (asciiCode % 90) + 10;
    }

    int asciiOfMyCity(const string &str)
    {
        unsigned asciiCode = 0;
        for (char sh : str)
            asciiCode = (asciiCode * 37 + static_cast<int>(tolower(sh))) % 10007;
        return asciiCode % 997;
    }

    // serch by country
    // on specific year
    void searchIncountry(Restaurant *root, int year) const
    {
        if (root != nullptr)
        {

            std::cout << "Restaurant: " << root->name << ", ID: " << root->id << root->sales.SalesOfYear(year) << std::endl;

            searchIncountry(root->left, year);
            searchIncountry(root->right, year);
        }
    }

    void searchIncountry(Restaurant *root, int year, int month) const
    {
        if (root != nullptr)
        {

            std::cout << "Restaurant: " << root->name << ", ID: " << root->id << root->sales.SalesOfMonth(year, month) << std::endl;

            searchIncountry(root->left, year, month);
            searchIncountry(root->right, year, month);
        }
    }
    void searchIncountry(Restaurant *root, int syear, int smonth, int sday, int eyear, int emonth, int eday) const
    {
        if (root != nullptr)
        {

            std::cout << "Restaurant: " << root->name << ", ID: " << root->id << root->sales.TotalSalesBetweenDates(syear, smonth, sday, eyear, emonth, eday) << std::endl;

            searchIncountry(root->left, syear, smonth, sday, eyear, emonth, eday);
            searchIncountry(root->right, syear, smonth, sday, eyear, emonth, eday);
        }
    }

    // Search by wilaya
    //  on specific year
    void searchByWilaya(Restaurant *root, int targetWilaya, int year) const
    {
        if (root != nullptr)
        {
            int restaurantWilaya = root->id / 1000000000LL; // Extract the wilaya part
            if (targetWilaya == restaurantWilaya || targetWilaya == 0)
            {
                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << root->sales.SalesOfYear(year) << std::endl;
            }
            searchByWilaya(root->left, targetWilaya, year);
            searchByWilaya(root->right, targetWilaya, year);
        }
    }
    // on specific month
    void searchByWilaya(Restaurant *root, int targetWilaya, int year, int month) const
    {
        if (root != nullptr)
        {
            int restaurantWilaya = root->id / 1000000000LL; // Extract the wilaya part
            if (targetWilaya == restaurantWilaya || targetWilaya == 0)
            {
                std::cout << "Restaurant: " << root->name << ", ID: "
                          << " total Sales in given Month  : " << root->id << root->sales.SalesOfMonth(year, month) << std::endl;
            }
            searchByWilaya(root->left, targetWilaya, year, month);
            searchByWilaya(root->right, targetWilaya, year, month);
        }
    }
    // on specific period
    void searchByWilaya(Restaurant *root, int targetWilaya, int Startyear, int StartMonth, int StartDay, int EndYear, int EndMonth, int EndDay) const
    {
        if (root != nullptr)
        {
            int restaurantWilaya = root->id / 1000000000LL; // Extract the wilaya part
            if (targetWilaya == restaurantWilaya || targetWilaya == 0)
            {
                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << root->sales.TotalSalesBetweenDates(Startyear, StartMonth, StartDay, EndYear, EndMonth, EndDay) << std::endl;
            }
            searchByWilaya(root->left, targetWilaya, Startyear, StartMonth, StartDay, EndYear, EndMonth, EndDay);
            searchByWilaya(root->right, targetWilaya, Startyear, StartMonth, StartDay, EndYear, EndMonth, EndDay);
        }
    }

    // Search by wilaya and city
    //  on specific year
    void searchByWilayaAndCity(Restaurant *root, int targetWilaya, int targetCity, int year) const
    {
        if (root != nullptr)
        {

            int restaurantWilaya = root->id / 1000000000LL;  // Extract the wilaya part
            int restaurantCity = (root->id / 1000LL) % 1000; // Extract the city part

            if ((targetWilaya == restaurantWilaya || targetWilaya == 0) &&
                    (targetCity == restaurantCity || targetCity == 0))
            {
                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << " the sales of specific year : " << root->sales.SalesOfYear(year) << std::endl;
            }

            searchByWilayaAndCity(root->left, targetWilaya, targetCity, year);
            searchByWilayaAndCity(root->right, targetWilaya, targetCity, year);
        }
    }

    // on specific month
    void searchByWilayaAndCity(Restaurant *root, int targetWilaya, int targetCity, int year, int month) const
    {
        if (root != nullptr)
        {

            int restaurantWilaya = root->id / 1000000000LL;  // Extract the wilaya part
            int restaurantCity = (root->id / 1000LL) % 1000; // Extract the city part
            if ((targetWilaya == restaurantWilaya || targetWilaya == 0) &&
                    (targetCity == restaurantCity || targetCity == 0))
            {

                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << " the sales of specific month : " << root->sales.SalesOfMonth(year, month) << std::endl;
            }

            searchByWilayaAndCity(root->left, targetWilaya, targetCity, year, month);
            searchByWilayaAndCity(root->right, targetWilaya, targetCity, year, month);
        }
    }

    // on specif period
    void searchByWilayaAndCity(Restaurant *root, int targetWilaya, int targetCity, int Syear, int Smonth, int Sday, int Eyear, int Emonth, int Eday) const
    {
        if (root != nullptr)
        {

            int restaurantWilaya = root->id / 1000000000LL;  // Extract the wilaya part
            int restaurantCity = (root->id / 1000LL) % 1000; // Extract the city part
            if ((targetWilaya == restaurantWilaya || targetWilaya == 0) &&
                    (targetCity == restaurantCity || targetCity == 0))
            {

                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << " the sales on specific period : " << root->sales.TotalSalesBetweenDates(Syear, Smonth, Sday, Eyear, Emonth, Eday) << std::endl;
            }

            searchByWilayaAndCity(root->left, targetWilaya, targetCity, Syear, Smonth, Sday, Eyear, Emonth, Eday);
            searchByWilayaAndCity(root->right, targetWilaya, targetCity, Syear, Smonth, Sday, Eyear, Emonth, Eday);
        }
    }

    // Search by wilaya, city, and district
    // on specific year
    void searchByWilayaCityAndDistrict(Restaurant *root, int targetWilaya, int targetCity, int targetDistrict, int year)
    {
        if (root != nullptr)
        {

            int restaurantWilaya = root->id / 1000000000LL;         // Extract the wilaya part
            int restaurantCity = (root->id / 1000LL) % 1000;        // Extract the city part
            int restaurantDistrict = (root->id / 1000000LL) % 1000; // Extract the district part
            if ((targetWilaya == restaurantWilaya || targetWilaya == 0) &&
                    (targetCity == restaurantCity || targetCity == 0) &&
                    (targetDistrict == restaurantDistrict || targetDistrict == 0))
            {
                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << " the sales on specific year : " << root->sales.SalesOfYear(year) << endl;
            }

            searchByWilayaCityAndDistrict(root->left, targetWilaya, targetCity, targetDistrict, year);
            searchByWilayaCityAndDistrict(root->right, targetWilaya, targetCity, targetDistrict, year);
        }
    }

    // on specific month
    void searchByWilayaCityAndDistrict(Restaurant *root, int targetWilaya, int targetCity, int targetDistrict, int year, int month) const
    {
        if (root != nullptr)
        {

            int restaurantWilaya = root->id / 1000000000LL;         // Extract the wilaya part
            int restaurantCity = (root->id / 1000LL) % 1000;        // Extract the city part
            int restaurantDistrict = (root->id / 1000000LL) % 1000; // Extract the district part
            if ((targetWilaya == restaurantWilaya || targetWilaya == 0) &&
                    (targetCity == restaurantCity || targetCity == 0) &&
                    (targetDistrict == restaurantDistrict || targetDistrict == 0))
            {
                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << " the sales on specific month : " << root->sales.SalesOfMonthForRatioFun(year, month) << endl;
            }
            searchByWilayaCityAndDistrict(root->left, targetWilaya, targetCity, targetDistrict, year, month);
            searchByWilayaCityAndDistrict(root->right, targetWilaya, targetCity, targetDistrict, year, month);
        }
    }

    // on specific period
    void searchByWilayaCityAndDistrict(Restaurant *root, int targetWilaya, int targetCity, int targetDistrict, int Syear, int Smonth, int Sday, int Eyear, int Emonth, int Eday) const
    {
        if (root != nullptr)
        {

            int restaurantWilaya = root->id / 1000000000LL;         // Extract the wilaya part
            int restaurantCity = (root->id / 1000LL) % 1000;        // Extract the city part
            int restaurantDistrict = (root->id / 1000000LL) % 1000; // Extract the district part
            if ((targetWilaya == restaurantWilaya || targetWilaya == 0) &&
                    (targetCity == restaurantCity || targetCity == 0) &&
                    (targetDistrict == restaurantDistrict || targetDistrict == 0))
            {
                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << " the sales on specific period : " << root->sales.TotalSalesBetweenDates(Syear, Smonth, Sday, Eyear, Emonth, Eday) << endl;
            }
            searchByWilayaCityAndDistrict(root->left, targetWilaya, targetCity, targetDistrict, Syear, Smonth, Sday, Eyear, Emonth, Eday);
            searchByWilayaCityAndDistrict(root->right, targetWilaya, targetCity, targetDistrict, Syear, Smonth, Sday, Eyear, Emonth, Eday);
        }
    }

    // print the ratio
    // on specific wilaya and city
    void ListRatioWilayaCity(Restaurant *root, int targetWilaya, int targetCity, int year, int month)
    {
        if (root != nullptr)
        {
            int restaurantWilaya = root->id / 1000000000LL;  // Extract the wilaya part
            int restaurantCity = (root->id / 1000LL) % 1000; // Extract the city part
            if ((targetWilaya == restaurantWilaya || targetWilaya == 0) &&
                    (targetCity == restaurantCity || targetCity == 0))
            {
                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << " the ratio  : " << Caluclate_ratio(root->sales, root->cost, year, month) << std::endl;
            }
            ListRatioWilayaCity(root->left, targetWilaya, targetCity, year, month);
            ListRatioWilayaCity(root->right, targetWilaya, targetCity, year, month);
        }
    }

    // print the ratio
    // on specific wilaya
    void ListRatioWilaya(Restaurant *root, int targetWilaya, int year, int month)
    {
        if (root != nullptr)
        {
            int restaurantWilaya = root->id / 1000000000LL; // Extract the wilaya part
            if (targetWilaya == restaurantWilaya || targetWilaya == 0)
            {
                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << " the ratio  : " << Caluclate_ratio(root->sales, root->cost, year, month) << std::endl;
            }
            ListRatioWilaya(root->left, targetWilaya, year, month);
            ListRatioWilaya(root->right, targetWilaya, year, month);
        }
    }

    // print the ratio
    // on specific restaurant
    void ListRatioID(Restaurant *root, long long id, int year, int month)
    {
        if (root != nullptr)
        {
            long long ID = root->id;
            if (ID == id)
            {
                std::cout << "Restaurant: " << root->name << ", ID: " << root->id << " the ratio  : " << Caluclate_ratio(root->sales, root->cost, year, month) << std::endl;
            }
            ListRatioID(root->left, id, year, month);
            ListRatioID(root->right, id, year, month);
        }
    }

    // Whole Country
    void ListRatioWholeCountry(Restaurant *root, int year, int month)
    {
        if (root != nullptr)
        {
            std::cout << "Restaurant: " << root->name << ", ID: " << root->id << " the ratio  : " << Caluclate_ratio(root->sales, root->cost, year, month) << std::endl;

            ListRatioWholeCountry(root->left, year, month);
            ListRatioWholeCountry(root->right, year, month);
        }
    }

public:
    // BIG FIVE
    // hannen

    RestaurantChainManagementSystem() : root(nullptr) {} // Default constructor + initializer list
    ~RestaurantChainManagementSystem()                   // Destructor
    {
        clear(root);
    }
    RestaurantChainManagementSystem(const RestaurantChainManagementSystem &rhs) : root(nullptr) // copy coonstructor
    {
        root = clone(rhs.root);
    }
    RestaurantChainManagementSystem(RestaurantChainManagementSystem &&rhs) : root{rhs.root} // move constructor
    {
        rhs.root = nullptr;
    }
    RestaurantChainManagementSystem &operator=(const RestaurantChainManagementSystem &rhs) // copy assignement constructor
    {
        RestaurantChainManagementSystem copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    void addRestaurant(std::string name, long long id, std::string owner, int numEmployee, SalesRestaurant s, CostsRestaurant c)
    {
        Restaurant *newRestaurant = new Restaurant(name, id, owner, numEmployee, nullptr, nullptr, std::move(s), std::move(c));
        insert(root, newRestaurant);
    }

    void readAndInsertDataFromFile(const std::string &restaurantFilename, const std::string &salesCostsFilename)
    {
        // Read restaurant data from the first file
        std::ifstream restaurantFile(restaurantFilename);

        if (!restaurantFile.is_open())
        {
            std::cerr << "Error opening restaurant file: " << restaurantFilename << std::endl;
            return;
        }

        //   std::cerr << "Reading restaurant data from file: " << restaurantFilename << std::endl;

        std::string restaurantLine;
        while (std::getline(restaurantFile, restaurantLine))
        {

            SalesRestaurant sales(24);
            CostsRestaurant cost(24);
            //   std::cerr << "Read line from restaurant file: " << restaurantLine << std::endl;

            std::stringstream ss(restaurantLine);
            std::string token;
            std::string name, ownership, wilaya, city, district, date;
            long long id;
            int numEmployees;

            // Assuming CSV format: name,ownership,numEmployee,wilaya,city,district,date,id
            std::getline(ss, name, ',');
            std::getline(ss, ownership, ',');

            if (std::getline(ss, token, ','))
            {
                try
                {
                    numEmployees = std::stoi(token);
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "Invalid argument exception when converting publicity: " << e.what() << std::endl;
                    continue; // Skip this line and move to the next one
                }
            }
            // ss.ignore(); // Ignore the comma
            std::getline(ss, wilaya, ',');
            std::getline(ss, city, ',');
            std::getline(ss, district, ',');
            std::getline(ss, date, ',');

            if (std::getline(ss, token, ','))
            {
                try
                {
                    id = std::stoll(token);
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "Invalid argument exception when converting ID: " << e.what() << std::endl;
                    continue; // Skip this line and move to the next one
                }
            }

            //  std::cerr << "Read restaurant: " << name << ", ID: " << id << std::endl;

            std::ifstream salesCostsFile(salesCostsFilename);

            if (!salesCostsFile.is_open())
            {
                std::cerr << "Error opening sales and costs file: " << salesCostsFilename << std::endl;
                return;
            }

            //  std::cerr << "Reading sales and costs from file: " << salesCostsFilename << std::endl;
            std::string salesCostsLine;
            while (std::getline(salesCostsFile, salesCostsLine))
            {
                std::stringstream ss(salesCostsLine);

                long long salesCostId;
                int year, month, day;
                double Algerian_sales, Indian_sales, Chinese_sales, Syrian_sales, Europ_sales;
                double rent;
                double employees;
                double electricity;
                double gas;
                double vegetables;
                double meats;
                double otherIngredients;
                double publicity;
                double other;

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        salesCostId = std::stoll(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //     std::cerr << "Invalid argument exception when converting ID: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (std::getline(ss, token, '-'))
                    year = std::stoi(token);
                if (std::getline(ss, token, '-'))
                    month = std::stoi(token);
                if (std::getline(ss, token, ','))
                    day = std::stoi(token);

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        Algerian_sales = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //  std::cerr << "Invalid argument exception when converting Algerian_sales: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }
                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        Indian_sales = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //    std::cerr << "Invalid argument exception when converting Algerian_sales: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        Chinese_sales = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //     std::cerr << "Invalid argument exception when converting Algerian_sales: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }
                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        Syrian_sales = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        // std::cerr << "Invalid argument exception when converting Algerian_sales: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }
                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        Europ_sales = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        // std::cerr << "Invalid argument exception when converting Algerian_sales: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        rent = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //    std::cerr << "Invalid argument exception when converting rent: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        employees = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //    std::cerr << "Invalid argument exception when converting employees: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }
                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        electricity = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cerr << "Invalid argument exception when converting electricity: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        gas = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cerr << "Invalid argument exception when converting gas: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        vegetables = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //    std::cerr << "Invalid argument exception when converting vegetables: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        meats = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //     std::cerr << "Invalid argument exception when converting meats: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        otherIngredients = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //    std::cerr << "Invalid argument exception when converting otherIngredients: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        publicity = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //     std::cerr << "Invalid argument exception when converting publicity: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (std::getline(ss, token, ','))
                {
                    try
                    {
                        other = std::stod(token);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        //   std::cerr << "Invalid argument exception when converting other: " << e.what() << std::endl;
                        continue; // Skip this line and move to the next one
                    }
                }

                if (salesCostId == id)
                {
                    // Create a new restaurant
                    // Update sales and costs for the restaurant
                    sales.recordSales(year, month, day, Algerian_sales, Indian_sales, Chinese_sales, Syrian_sales, Europ_sales);
                    cost.recordCost(year, month, day, rent, employees, electricity, gas, vegetables, meats, otherIngredients, publicity, other);

                    // std::cerr << "Creating restaurant with ID: " << id << std::endl;
                    // std::cerr << "Finished reading and inserting data." << std::endl;
                }
            }

            addRestaurant(name, id, ownership, numEmployees, std::move(sales), std::move(cost));
            salesCostsFile.close();
        }
        restaurantFile.close();
    }

    Restaurant *getRoot()
    {
        return root;
    }

    // Function to print all restaurants with sales and costs
    void printAllRestaurants()
    {
        cout << " the restaurant in our system are : " << endl;
        printInOrder(root);
    }

    void printInOrder(Restaurant *root)
    {
        if (root != nullptr)
        {
            // Traverse left subtree
            printInOrder(root->left);

            // Print current node's data
            std::cout << "Name: " << root->name << ", ID: " << root->id << " Number OF Employees:  " << root->numEmployees << "  Owner : " << root->ownership << endl;

            //   std::cout<<" the costs of the year :" << root->cost.TotalCostYear(2023) <<endl ;
            // std::cout<<" the sales of the year :" << root->sales.SalesOfYear(2023) <<endl ;

            // Traverse right subtree
            printInOrder(root->right);
        }
    }

    double calculateAmount(Restaurant *root, int year, int month, const std::string &type)
    {
        std::ifstream infile("rating.csv");
        if (!infile)
        {
            std::cerr << "Error opening Rating.csv" << std::endl;
            return 0.0; // or another appropriate default value
        }

        std::string line;

        // Skip header line
        getline(infile, line);

        while (std::getline(infile, line))
        {
            std::stringstream ss(line);
            std::string ID, Year, Month, Algerian_Rate, Syrian_Rate, Chinese_Rate, European_Rate, Indian_Rate;

            getline(ss, ID, ',');
            getline(ss, Year, ',');
            getline(ss, Month, ',');
            getline(ss, Algerian_Rate, ',');
            getline(ss, Syrian_Rate, ',');
            getline(ss, Chinese_Rate, ',');
            getline(ss, European_Rate, ',');
            getline(ss, Indian_Rate);

            try
            {
                int iyear = std::stoi(Year);
                int imonth = std::stoi(Month);
                long long id = std::stoll(ID);

                if (id == root->id && iyear == year && imonth == month)
                {
                    std::string transformedType = type;
                    std::transform(transformedType.begin(), transformedType.end(), transformedType.begin(), ::tolower);

                    std::cout << std::fixed << std::setprecision(3);
                    double cuisineSales = root->sales.displayMonthlySalesForCuisine(year, month, type);

                    if (transformedType == "algerian")
                    {

                        return cuisineSales + std::stod(Algerian_Rate) / 100;
                    }
                    else if (transformedType == "syrian")
                    {
                        return cuisineSales + std::stod(Syrian_Rate) / 100;
                    }
                    else if (transformedType == "chinese")
                    {
                        return cuisineSales + std::stod(Chinese_Rate) / 100;
                    }
                    else if (transformedType == "european")
                    {
                        return cuisineSales + std::stod(European_Rate) / 100;
                    }
                    else if (transformedType == "indian")
                    {
                        return cuisineSales + std::stod(Indian_Rate) / 100;
                    }
                }
            }

            catch (const std::invalid_argument &e)
            {
                std::cerr << "Invalid argument exception: " << e.what() << std::endl;
                // Handle the exception, e.g., log the error, return a default value, etc.
                return 0.0;
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << "Out of range exception: " << e.what() << std::endl;
                // Handle the exception, e.g., log the error, return a default value, etc.
                return 0.0;
            }
        }

        // If no matching entry is found, return a default value
        return 0.0; // or another appropriate default value
    }

    void theWinnersOfTheNationalPrize(int month, int year)
    {
        vector<string> theFiveWinners;
        theFiveWinners.push_back(determineWinners(root, month, year, "Algerian")->name);
        theFiveWinners.push_back(determineWinners(root, month, year, "Syrian")->name);
        theFiveWinners.push_back(determineWinners(root, month, year, "Chinese")->name);
        theFiveWinners.push_back(determineWinners(root, month, year, "Indian")->name);
        theFiveWinners.push_back(determineWinners(root, month, year, "European")->name);
        cout << endl;
        // return theFiveWinners;
        cout << "the name of restaurant which its Algerian cuisine won in  Date " << year << "/" << month << "  is: ";
        cout << theFiveWinners[0] << endl;
        cout << "the name of restaurant which its Syrian cuisine won in  Date " << year << "/" << month << "  is: ";
        cout << theFiveWinners[1] << endl;
        cout << "the name of restaurant which its Chinese cuisine won in  Date " << year << "/" << month << "  is: ";
        cout << theFiveWinners[2] << endl;
        cout << "the name of restaurant which its Indian cuisine won in  Date " << year << "/" << month << "  is: ";
        cout << theFiveWinners[3] << endl;
        cout << "the name of restaurant which its European cuisine won in  Date " << year << "/" << month << "  is: ";
        cout << theFiveWinners[4] << endl;
    }

    // Function to search for restaurants based on wilaya
    // the 3 version
    void searchRestaurant(const std::string &wilaya, int year)
    {
        cout << " All the Restaurants of the wilaya : " << wilaya << endl;
        int targetWilaya = asciiOfMyString(wilaya);

        searchByWilaya(root, targetWilaya, year);
    }

    void searchRestaurant(const std::string &wilaya, int year, int month)
    {
        cout << " All the Restaurants of the wilaya : " << wilaya << endl;
        int targetWilaya = asciiOfMyString(wilaya);

        searchByWilaya(root, targetWilaya, year, month);
    }

    void searchRestaurant(const std::string &wilaya, int syear, int smonth, int sday, int eyear, int emonth, int eday)
    {
        cout << " All the Restaurants of the wilaya : " << wilaya << endl;
        int targetWilaya = asciiOfMyString(wilaya);
        searchByWilaya(root, targetWilaya, syear, smonth, sday, eyear, emonth, eday);
    }

    // Function to search for restaurants based on wilaya and city

    // the 3 version
    void searchRestaurant(const std::string &wilaya, const std::string &city, int year)
    {
        cout << " All the Restaurants of the wilaya : " << wilaya << " and city " << city << endl;
        int targetWilaya = asciiOfMyString(wilaya);

        int targetCity = asciiOfMyCity(city);
        searchByWilayaAndCity(root, targetWilaya, targetCity, year);
    }

    void searchRestaurant(const std::string &wilaya, const std::string &city, int year, int month)
    {
        cout << " All the Restaurants of the wilaya : " << wilaya << " and city " << city << endl;
        int targetWilaya = asciiOfMyString(wilaya);
        int targetCity = asciiOfMyCity(city);
        searchByWilayaAndCity(root, targetWilaya, targetCity, year, month);
    }

    void searchRestaurant(const std::string &wilaya, const std::string &city, int syear, int smonth, int sday, int eyear, int emonth, int eday)
    {
        cout << " All the Restaurants of the wilaya : " << wilaya << " and city " << city << endl;
        int targetWilaya = asciiOfMyString(wilaya);
        int targetCity = asciiOfMyCity(city);
        searchByWilayaAndCity(root, targetWilaya, targetCity, syear, smonth, sday, eyear, emonth, eday);
    }

    // Function to search for restaurants based on wilaya, city, and district
    // 3 versions
    void searchRestaurant(const std::string &wilaya, const std::string &city, const std::string &district, int year)
    {
        cout << " All the Restaurants of the wilaya : " << wilaya << " and city " << city << " and the district " << district << endl;
        int targetWilaya = asciiOfMyString(wilaya);
        int targetCity = asciiOfMyCity(city);
        int targetDistrict = asciiOfMyString(district);
        searchByWilayaCityAndDistrict(root, targetWilaya, targetCity, targetDistrict, year);
    }

    void searchRestaurant(const std::string &wilaya, const std::string &city, const std::string &district, int year, int month)
    {
        cout << " All the Restaurants of the wilaya : " << wilaya << " and city " << city << " and the district " << district << endl;
        int targetWilaya = asciiOfMyString(wilaya);
        int targetCity = asciiOfMyCity(city);
        int targetDistrict = asciiOfMyString(district);
        searchByWilayaCityAndDistrict(root, targetWilaya, targetCity, targetDistrict, year, month);
    }

    void searchRestaurant(const std::string &wilaya, const std::string &city, const std::string &district, int syear, int smonth, int sday, int eyear, int emonth, int eday)
    {
        cout << " Al the Restaurants of the wilaya : " << wilaya << " and city " << city << " and the district " << district << endl;
        int targetWilaya = asciiOfMyString(wilaya);
        int targetCity = asciiOfMyCity(city);
        int targetDistrict = asciiOfMyString(district);
        searchByWilayaCityAndDistrict(root, targetWilaya, targetCity, targetDistrict, syear, smonth, sday, eyear, emonth, eday);
    }

    // print the ratio  3 versions
    void ListRatio(const std::string &wilaya, int year, int month)
    {
        cout << " All the Restaurants of the wilaya : " << wilaya << endl;
        int targetWilaya = asciiOfMyString(wilaya);
        ListRatioWilaya(root, targetWilaya, year, month);
    }

    void ListRatio(const std::string &wilaya, const std::string &city, int year, int month)
    {
        cout << " All the Restaurants of the wilaya : " << wilaya << " and city " << city << endl;
        int targetWilaya = asciiOfMyString(wilaya);
        int targetCity = asciiOfMyCity(city);
        ListRatioWilayaCity(root, targetWilaya, targetCity, year, month);
    }
    void ListRatio(long long id, int year, int month)
    {
        ListRatioID(root, id, year, month);
    }

    void ListRatio(int year, int month)
    {
        ListRatioWholeCountry(root, year, month);
    }

    // searchIncountry
    // 3 versions

    void searchCountry(int year)
    {
        cout << " All the restaurants in country  " << year << endl;
        searchIncountry(root, year);
    }

    void searchCountry(int year, int month)
    {
        cout << " All  the restaurants in country  " << year << "/" << month << endl;
        searchIncountry(root, year, month);
    }
    void searchCountry(int syear, int smonth, int sday, int eyear, int emonth, int eday)
    {
        cout << " All the  restaurants in country from  year" << syear << " /" << smonth << "/" << sday << " to : " << eyear << "/" << emonth << "/" << eday << endl;
        searchIncountry(root, syear, smonth, sday, eyear, emonth, eday);
    }
};

int main()
{

    auto start = std::chrono::high_resolution_clock::now();

    LinkFile linkFile;
    // Insert a sample restaurant data into the CSV file
    ofstream testfile("C:\\xampp\\htdocs\\Bouzira Maroua\\code\\dba.csv", ios::app);
    testfile.close();
    // Test reading and updating the ID
    linkFile.readId();

    // Create an Object of RestaurantChainManagementSystem
    RestaurantChainManagementSystem KolHani ;

    //  restaurant data  files and sales/costs data
    std::string restaurantFilename = "C:\\xampp\\htdocs\\Bouzira Maroua\\code\\dba.csv";
    std::string costsSalesFilename =  "C:\\xampp\\htdocs\\Bouzira Maroua\\code\\dbaforSalesCosts.csv";

    // Read and insert data from files

    KolHani.readAndInsertDataFromFile(restaurantFilename, costsSalesFilename);

    // Display the inserted restaurant data (for demonstration purposes)
    KolHani.printAllRestaurants();
    cout << endl;

    cout << " the report of the sales of any restaurant in any month : " << endl;
    KolHani.searchCountry(2023, 1);

    cout << endl;
    cout << endl;

    //  cout <<" listing summarizing all the sales of all restaurants in a given wilaya in given period  :"  << endl ;
    KolHani.searchRestaurant("tipaza", 2021, 1, 1, 2023, 12, 12);

    cout << endl;
    cout << endl;

    // cout <<" listing summarizing all the sales of all restaurants in a given city in given month :"  << endl ;
    KolHani.searchRestaurant("Setif", "Tourist Lane", 2023, 1);

    cout << endl;
    cout << endl;

    // cout <<" listing summarizing all the sales of all restaurants in a given district in given year :"  << endl ;
    KolHani.searchRestaurant("Oran", "Harbor Avenue", "Harbor", 2023);
    cout << endl;
    cout << endl;

    // cout <<" listing summarizing all the sales of all restaurants in a given district in given year :"  << endl ;
    KolHani.searchRestaurant("Oran", "", "Harbor", 2023);
    cout << endl;
    cout << endl;

    KolHani.searchRestaurant("Oran", "Harbor Avenue", 2023);
    cout << endl;
    cout << endl;

    cout << endl;
    cout << endl;

    KolHani.theWinnersOfTheNationalPrize(1, 2023);
    // cout << endl;
    cout << endl;
    cout << endl;

    cout << " listing summarizing  the ratio of the monthly sales to the amount of money spent during any given month on publicity for a specified restaurant   :" << endl;
    KolHani.ListRatio(645152561001, 2023, 01);

    cout << endl;

    cout << " listing summarizing  the ratio of the monthly sales to the amount of money spent during any given month on publicity for a specified wilaya  :" << endl;
    KolHani.ListRatio("Oran", 2023, 1);

    cout << endl;

    cout << " listing summarizing  the ratio of the monthly sales to the amount of money spent during any given month on publicity for a specified city   :" << endl;
    KolHani.ListRatio("Oran", "Harbor Avenue", 2023, 1);

    cout << endl;
    cout << endl;

    cout << " listing summarizing  the ratio of the monthly sales to the amount of money spent during any given month on publicity for the whole country  :" << endl;
    KolHani.ListRatio(2023, 1);

    cout << endl;
    cout << endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Time taken to  print result : " << duration.count() << " milliseconds." << std::endl;

    return 0;
}
