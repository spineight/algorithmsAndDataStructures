import trade.AbstractServer
import trade.TradeServer
import java.util.concurrent.Executors
import java.util.concurrent.TimeUnit


fun main() {
    val tinOutServer: AbstractServer = TradeServer(8081)
    val threadPool = Executors.newFixedThreadPool(1)
    threadPool.submit(tinOutServer)
    threadPool.shutdown()
    try {
        threadPool.awaitTermination(Long.MAX_VALUE, TimeUnit.MINUTES)
    } catch (ignored: InterruptedException) {
    }
}
