package trade


import io.reactivex.netty.protocol.http.server.HttpServer;
import io.netty.handler.codec.http.HttpResponseStatus
import rx.Observable

abstract class AbstractServer(private val port: Int) : Runnable {
    class Pair {
        var response: Observable<String>? = null
        var status: HttpResponseStatus? = null
    }

    abstract fun act(queryParam: Map<String, List<String>>, action: String?): Pair
    override fun run() {
        HttpServer.newServer(port).start { req, resp ->
            val action: String = req.decodedPath.substring(1)
            val queryParam: Map<String, List<String>> =
                req.queryParameters
            val response = act(queryParam, action)
            resp.status = response.status
            resp.writeString(response.response)
        }.awaitShutdown()
    }
}