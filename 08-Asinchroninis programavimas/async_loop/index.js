const {XMLParser} = require("fast-xml-parser");

async function downloadCurrencyRateXml(currency) {
    const url = new URL("https://www.lb.lt/webservices/fxrates/FxRates.asmx/getFxRatesForCurrency");
    const now = new Date();
    const today = `${now.getFullYear()}-${now.getMonth() + 1}-${now.getDate()}`;
    url.searchParams.set("tp", "LT");
    url.searchParams.set("ccy", currency);
    url.searchParams.set("dtFrom", today);
    url.searchParams.set("dtTo", today);
    const response = await fetch(url);
    return await response.text();
}

async function parseCurrencyRate(response, currency) {
    const parser = new XMLParser();
    const data = parser.parse(response);
    const ccyAmtElements = data['FxRates']['FxRate']['CcyAmt'];
    const ccyAmtForCurrency = ccyAmtElements.filter(el => el['Ccy'] === currency)[0];
    return ccyAmtForCurrency['Amt'];
}

async function getCurrencyExchangeRate(currency) {
    const responseXml = await downloadCurrencyRateXml(currency);
    return {
        rate: await parseCurrencyRate(responseXml, currency),
        currency: currency
    };
}

async function getExchangeRates(currencies) {
    const rates = currencies.map(getCurrencyExchangeRate);
    for await (let rate of rates) {
        console.log(`1 EUR = ${rate.rate} ${rate.currency}`);
    }
}

const currencies = ['PLN', 'SEK', 'DKK', 'NOK', 'USD'];
getExchangeRates(currencies);

