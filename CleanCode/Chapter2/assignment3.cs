public class CustomerSearch
{
    public List<Customer> queryDatabase(string databaseName){
        var query = from c in db.customers
                    where c.Country.Contains(databaseName)
                    orderby c.CustomerID ascending
                    select c;

        return query.ToList();
    }
    
    public List<Customer> SearchByCountry(string country)
    {
        return queryDatabase(country);
    }

    public List<Customer> SearchByCompanyName(string company)
    {
        return queryDatabase(company);
    }

    public List<Customer> SearchByContact(string contact)
    {
        return queryDatabase(contact);
    }

    public string ExportToCSV(List<Customer> customerData)
    {
        StringBuilder csvString = new StringBuilder();

        foreach (var customer in customerData)
        {
            csvString.AppendFormat("{0}, {1}, {2}, {3}", customer.CustomerID, customer.CompanyName, customer.ContactName, customer.Country);
            csvString.AppendLine();
        }

        return csvString.ToString();
    }
}
