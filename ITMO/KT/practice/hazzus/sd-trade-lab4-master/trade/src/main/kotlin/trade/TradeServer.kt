package trade

import io.netty.handler.codec.http.HttpResponseStatus
import rx.Observable
import java.util.*


class TradeServer(port: Int) : AbstractServer(port) {
    private val companies: MutableMap<Int, Company> = HashMap<Int, Company>()
    private val traders: MutableMap<Int, Trader> = HashMap<Int, Trader>()
    override fun act(queryParam: Map<String, List<String>>, action: String?): Pair {
        val resp = Pair()
        when (action) {
            "add_company" -> {
                resp.response = addCompany(queryParam)
                resp.status = HttpResponseStatus.OK
            }
            "add_shares" -> {
                resp.response = addShares(queryParam)
                resp.status = HttpResponseStatus.OK
            }
            "change_price" -> {
                resp.response = changePrice(queryParam)
                resp.status = HttpResponseStatus.OK
            }
            "add_trader" -> {
                resp.response = addTrader(queryParam)
                resp.status = HttpResponseStatus.OK
            }
            "buy_shares" -> {
                resp.response = buyShares(queryParam)
                resp.status = HttpResponseStatus.OK
            }
            "sell_shares" -> {
                resp.response = sellShares(queryParam)
                resp.status = HttpResponseStatus.OK
            }
            "list_shares" -> {
                resp.response = listShares(queryParam)
                resp.status = HttpResponseStatus.OK
            }
            "drop" -> {
                companies.clear()
                traders.clear()
            }
            else -> {
                resp.response = Observable.just("bad request")
                resp.status = HttpResponseStatus.BAD_REQUEST
            }
        }
        return resp
    }

    private fun addCompany(queryParam: Map<String, List<String>>): Observable<String> {
        val id: Int = queryParam["id"]!![0].toInt()
        val name = queryParam["name"]!![0]
        if (companies.containsKey(id)) {
            return Observable.just("Already exist")
        }
        companies.put(id, Company(name, 0, 0))
        return Observable.just("ok")
    }

    private fun changePrice(queryParam: Map<String, List<String>>): Observable<String> {
        val id: Int = queryParam["id"]!![0].toInt()
        val price: Int = queryParam["price"]!![0].toInt()
        if (!companies.containsKey(id)) {
            return Observable.just(companies.toString())
        }
        val comp: Company = companies[id]!!
        comp.price = price
        return Observable.just("ok")
    }

    private fun addTrader(queryParam: Map<String, List<String>>): Observable<String> {
        val id: Int = queryParam["id"]!![0].toInt()
        val name = queryParam["name"]!![0]
        val money: Int = queryParam["money"]!![0].toInt()
        if (traders.containsKey(id)) {
            return Observable.just("Already exist")
        }
        traders.put(id, Trader(name, money))
        return Observable.just("ok")
    }

    private fun addShares(queryParam: Map<String, List<String>>): Observable<String> {
        val id: Int = queryParam["id"]!![0].toInt()
        val amount: Int = queryParam["amount"]!![0].toInt()
        if (!companies.containsKey(id)) {
            return Observable.just("No such company")
        }
        companies[id]!!.shares += amount
        return Observable.just("ok")
    }

    private fun buyShares(queryParam: Map<String, List<String>>): Observable<String> {
        val id: Int = queryParam["id"]!![0].toInt()
        val idComp: Int = queryParam["idComp"]!![0].toInt()
        val amount: Int = queryParam["amount"]!![0].toInt()
        if (!companies.containsKey(idComp)) {
            return Observable.just("No such company")
        }
        if (!traders.containsKey(id)) {
            return Observable.just("No such trader")
        }
        val trader: Trader = traders[id]!!
        val comp: Company = companies[idComp]!!
        if (comp.shares < amount) {
            return Observable.just("Not enough shares")
        }
        if (trader.money < amount * comp.price) {
            return Observable.just("Not enough money")
        }
        comp.shares -= amount
        trader.money -= amount * comp.price
        if (trader.shares.containsKey(comp)) {
            trader.shares.put(comp, trader.shares[comp]!! + amount)
        } else {
            trader.shares.put(comp, amount)
        }
        return Observable.just("ok")
    }

    private fun sellShares(queryParam: Map<String, List<String>>): Observable<String> {
        val id: Int = queryParam["id"]!![0].toInt()
        val idComp: Int = queryParam["idComp"]!![0].toInt()
        val amount: Int = queryParam["amount"]!![0].toInt()
        if (!companies.containsKey(idComp)) {
            return Observable.just("No such company")
        }
        if (!traders.containsKey(id)) {
            return Observable.just("No such trader")
        }
        val trader: Trader = traders[id]!!
        val comp: Company = companies[idComp]!!
        if (!trader.shares.containsKey(comp) || trader.shares[comp]!! < amount) {
            return Observable.just("Not enough shares")
        }
        comp.shares += amount
        trader.money += amount * comp.price
        trader.shares.put(comp, trader.shares[comp]!! - amount)
        if (trader.shares[comp] == 0) {
            trader.shares.remove(comp)
        }
        return Observable.just("ok")
    }

    private fun listShares(queryParam: Map<String, List<String>>): Observable<String> {
        val id: Int = queryParam["id"]!![0].toInt()
        if (!traders.containsKey(id)) {
            return Observable.just("No such trader")
        }
        val trader: Trader = traders[id]!!
        val builder = StringBuilder()
        var money = 0
        for (comp in trader.shares.keys) {
            builder.append(comp.name).append(" ").append(trader.shares[comp]).append(System.lineSeparator())
            money += comp.price * trader.shares[comp]!!
        }
        builder.append("Total money: ").append(trader.money).append(System.lineSeparator()).append("Money in shares: ")
            .append(money).append(
                System.lineSeparator()
            )
        return Observable.just(builder.toString())
    }
}