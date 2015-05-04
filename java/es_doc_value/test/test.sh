curl 'http://localhost:9200/skyeye-2015.03.26/_search?pretty' -d '
{
    "query": {
        "filtered": {
            "filter": {
                "bool": {
                    "must_not": [], 
                        "must": [
                            {
                                "range": {
                                    "@timestamp": {
                                        "lte": 1427256721447
                                    }
                                }
                            }]
                }
            }, 
            "query": {
                "query_string": {
                    \"query\": \"host:\"jonemaccane1.byethost7.com\"  OR  host:\"jpnspts.biz\"  OR  host:\"jpqueen.biz\"  OR  host:\"kaoal.chickenkiller.com\"  OR  host:\"laborsforum.org\"  OR  host:\"lakers.jumpingcrab.com\"  OR  host:\"limited.000space.com\"  OR  host:\"lookasjames.000space.com\"  OR  host:\"mansgepitostraig.com\"  OR  host:\"mechanicalcomfort.net\"  OR  host:\"microalba.serveftp.com\"  OR  host:\"microblo5.mooo.com\"  OR  host:\"microbrownys.strangled.net\"  OR  host:\"microchiefs.twilightparadox.com\"  OR  host:\"microchisk.mooo.com\"  OR  host:\"microchsse.strangled.net\"  OR  host:\"microdelta.crabdance.com\"  OR  host:\"microgenuinsman.servebeer.com\"  OR  host:\"microjonjokoss.jumpingcrab.com\"  OR  host:\"microlilics.000space.com\"  OR  host:\"microlilics.crabdance.com\"  OR  host:\"micromacrarusn.com\"  OR  host:\"micromacs.org\"  OR  host:\"micromichi.ezua.com\"  OR  host:\"micromps1.net\"  OR  host:\"micronames.jumpingcrab.com\"  OR  host:\"micronao.hopto.org\"  OR  host:\"micronaoko.jumpingcrab.com\"  OR  host:\"microos.jumpingcrab.com\"  OR  host:\"microplants.strangled.net\"  OR  host:\"microsoft-xpupdate.com\"  OR  host:\"microyours.ignorelist.com\"  OR  host:\"minshatopas12.org\"  OR  host:\"msdn4updates.com\"  OR  host:\"mshotfi.com\"  OR  host:\"msupdates.com\"  OR  host:\"myhome.serveuser.com\"  OR  host:\"myphone.freei.me\"  OR  host:\"nanogalsman.org\"  OR  host:\"nanomicsoft.com\"  OR  host:\"nanoocspos.com\"  OR  host:\"nanosleepss.net\"  OR  host:\"ncnbroadcasting.reportinside.net\"  OR  host:\"neao.biz\"  OR  host:\"neosilba.com\"  OR  host:\"new.freecinemaworld.net\"  OR  host:\"new.islamicawaken.com\"  OR  host:\"newsagencypool.com\"  OR  host:\"newsdailyinhk.com\"  OR  host:\"newsups.000a.biz\"  OR  host:\"nokasblog.agilityhoster.com\"  OR  host:\"offierevision.com\"  OR  host:\"online.usean.biz\"  OR  host:\"outlookz.com\"  OR  host:\"pb.enewslive.org\"  OR  host:\"pb.qocp.net\"  OR  host:\"pb.upinfo.biz\"  OR  host:\"photo.eonlineworld.com\"  OR  host:\"popin.0fees.net\"  OR  host:\"private.neao.biz\"  OR  host:\"proteingainer.biz\"  OR  host:\"rainbowbbs.mywebcommunity.org\"  OR  host:\"rayp.biz\"  OR  host:\"re.policyforums.org\"  OR  host:\"redblacksleep.createandhost.com\"  OR  host:\"redlooksman.servehttp.com\"  OR  host:\"reportinshop.com\"  OR  host:\"reportinside.net\"  OR  host:\"rootca.000space.com\"  OR  host:\"sales.eu5.org\"  OR  host:\"secureonline.net\"  OR  host:\"self-makeups.com\"  OR  host:\"self-makingups.com\"  OR  host:\"sellingconnection.org\"  OR  host:\"sens.humanforum.net\"  OR  host:\"shndia.com\"  OR  host:\"silverbell.000space.com\"  OR  host:\"sipapals.servehalflfe.com\"  OR  host:\"smartappactiv.com\"  OR  host:\"smartnewup.crabdance.com\"  OR  host:\"sourcecodecenter.org\"  OR  host:\"spotnews.com\"  OR  host:\"st.cloins.com\"  OR  host:\"stloelementry.200gigs.com\"  OR  host:\"students.serveblog.net\"  OR  host:\"support¬forum.org\"  OR  host:\"supportforum.org\"  OR  host:\"terryblog.110mB.com\"  OR  host:\"thenewesthta.mypressonline.com\"  OR  host:\"thirdbase.bugs3.com\"  OR  host:\"todaynewscentre.net\"  OR  host:\"tradeinf.com\"  OR  host:\"unknown12.ignorelist.com\"  OR  host:\"updaairpush.ignorelist.com\"  OR  host:\"updaily.biz.nf\"  OR  host:\"updaily.phpnet.us\"  OR  host:\"updaisin.net16.net\"  OR  host:\"updalsim.freehostee.com\"  OR  host:\"updarling.000a.biz\"  OR  host:\"updatable.20x.cc\"\"
                }
            }
        }
    }, 
    "aggs": {
        "sip": {
            "terms": {
                "field": "sip", 
                "size": 500
            }, 
            "aggs": {
                "top_sip_hits": {
                    "top_hits": {
                        "sort": [
                            {
                                "@timestamp": {"order": "asc"}
                            }], 
                        "size": 1}
                }
            }
        }
    }, 
    "size": 0
}

