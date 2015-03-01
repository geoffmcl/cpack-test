

#include <QtDebug>


#include <QUrl>
#include <QScriptEngine>
#include <QScriptValue>

#include "xobjects/servercall.h"

ServerCall::ServerCall( QObject *parent) :
    QObject(parent)
{
    //M = mob;
    netMan = new QNetworkAccessManager(this);

}

void ServerCall::get_record(QString url, int id)
{
    QString u = QString("/%1/%2").arg(url).arg(QString::number(id));
    get(u);

}

void ServerCall::get(QString url)
{
    QHash<QString, QString> vars;
    this->get(url, vars);
}

void ServerCall::get(QString url, QHash<QString, QString> vars)
{
    QUrl urlx(url);
    //urlx.setScheme("http");
    //urlx.setHost("127.0.0.1");
    //urlx.setPort(5000);
    //urlx.setPath( QString("/rpc%1").arg(url) );
    QHashIterator<QString, QString> i(vars);
     while (i.hasNext()) {
         i.next();
         urlx.addQueryItem(i.key(), i.value());
     }

    qDebug() << urlx.toString();

    serverString = "";
    QNetworkRequest request;
    request.setUrl(urlx);
    //return;
    reply = netMan->get(request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(on_server_ready_read()) );
    connect(reply, SIGNAL(finished()), this, SLOT(on_server_read_finished()) );
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(on_server_error(QNetworkReply::NetworkError)));
}

/*
def fetch(self, fetch_url, params, xWidget, debugMode=False):

        self.widget = xWidget
        self.params = params
        if debugMode:
                self.debug = debugMode

        #print self.settings.server_url()
        srv_url = self.settings.server_url()
        if srv_url == None:
                print "NO URL in dServer.fetch()"
                return
        self.url = QtCore.QUrl( "%s%s" % (srv_url, fetch_url) )
        if self.params:
                for p in self.params:
                        self.url.addQueryItem( str(p), str(self.params[p]) )

        self.request = QtNetwork.QNetworkRequest()
        self.request.setUrl( self.url )
        self.load_cookies()

        if self.debug:
                print "\n--------------------------------------------------"
                print ">> fetch: "
                print "       %s" %  self.url.toString()

        self.update_status(BUSY)
        self.error = False
        self.abort_flag = False
        self.timeoutTimer.start()
        self.POST = False
        self.reply = self.netMan.get( self.request)
        self.connect(self.reply, QtCore.SIGNAL( 'error(QNetworkReply::NetworkError)'), self.on_network_error)
        self.connect(self.reply, QtCore.SIGNAL( 'readyRead()'), self.on_server_ready_read)
        self.connect(self.reply, QtCore.SIGNAL( 'finished()'), self.on_server_read_finished)
 */


void ServerCall::post(QString url, QHash<QString, QString> payload)
{

    //= Encode Payload
    QUrl urlPayloadEncoder = QUrl();
    QHashIterator<QString, QString> ip(payload);
     while (ip.hasNext()) {
         ip.next();
         urlPayloadEncoder.addQueryItem(ip.key(), ip.value());
     }

     //urlParamsEncoder->addQueryItem( k, str(self.params[k]) )
    //self.postData =  urlParamsEncoder.encodedQuery()

    QUrl urlx;
    urlx.setScheme("http");
    urlx.setHost("192.168.5.12");
    urlx.setPort(4444);
    urlx.setPath(url);

    qDebug() << urlx.toString();

    serverString = "";
    QNetworkRequest request;
    request.setUrl(urlx);

    reply = netMan->post(request, urlPayloadEncoder.encodedQuery());
    connect(reply, SIGNAL(readyRead()), this, SLOT(on_server_ready_read()) );
    connect(reply, SIGNAL(finished()), this, SLOT(on_server_read_finished()) );
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(on_server_error(QNetworkReply::NetworkError)));
}
/*
def action(self, action_url, params=None, xWidget=None, debugMode=False):

                self.widget = xWidget
                self.params = params
                self.debug = debugMode

                #self.start_timer()

                ### Create factory URL and encode the "payload" using the QUrl object
                urlParamsEncoder = QtCore.QUrl()
                ##urlEncoder.addQueryItem( "action", actionName )
                for k in params:
                        urlParamsEncoder.addQueryItem( k, str(self.params[k]) )
                self.postData =  urlParamsEncoder.encodedQuery()


                self.url = QtCore.QUrl( "%s%s" % (self.settings.server_url(), action_url) )
                self.request = QtNetwork.QNetworkRequest()
                self.request.setUrl( self.url )
                self.load_cookies()

                #self.url = QtCore.QUrl( "%s%s" % (self.settings.server_rpc_url(), action_url) )
                #self.request.setUrl( self.url )
                #self.load_cookies()
                #if self.widget:
                #	if self.isStatusBar:
                #		self.widget.set_request_start( self.url.toString() )
                #	else:
                #		self.widget_saving()

                self.update_status(BUSY)
                self.error = False
                self.abort_flag = False
                self.timeoutTimer.start()
                #self.isSaving = True
                self.POST = True
                if self.debug:
                        print "\n--------------------------------------------------"
                        print ">> action: "
                        print "       %s" %  self.url.toString()

                self.reply = self.netMan.post( self.request, self.postData)
                self.connect(self.reply, QtCore.SIGNAL( 'error(QNetworkReply::NetworkError)'), self.on_network_error)
                self.connect(self.reply, QtCore.SIGNAL( 'readyRead()'), self.on_server_ready_read)
                self.connect(self.reply, QtCore.SIGNAL( 'finished()'), self.on_server_read_finished)

*/










void ServerCall::on_server_error(QNetworkReply::NetworkError code)
{
    qDebug() << "Error" << code << reply->errorString();
}

void ServerCall::on_server_ready_read()
{
    serverString.append(reply->readAll());
    //qDebug() << "Read"; // << serverString;
}

void ServerCall::on_server_read_finished()
{
     qDebug() << ">> got Data from server"; // << serverString;
      //QScriptValue json;
      QScriptEngine engine;
      QScriptValue json = engine.evaluate( "(" + serverString + ")");
      emit data(json);
}












void ServerCall::attach_statusbar(XStatusBar *sBar)
{
    this->statusBar = sBar;
}
