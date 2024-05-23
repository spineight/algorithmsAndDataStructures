package trade

import java.util.*

class Trader(var name: String, var money: Int) {
    var shares = HashMap<Company, Int>()
}

