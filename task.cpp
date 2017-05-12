#include <domainmodel.h>
/*this file includes function which return a string on performing certain tasks on the vm(aka domain)
 * each task is such that it can be called from qml
 */

static QMap <QString,int> tsk={//for the tasks
                               {"start",1},
                               {"pause",2},
                               {"stop",3},
                               {"state",4},
                               {"xml",5}
                              };

QString doTask(QString task, int index,Domain m_domain){
QString ret="nil";//if the intended task doesn't execute then nil is returend
int state = 0 ;//this is the default state
int reason ;
auto dom=m_domain.m_dom;//variable to hold the domain pointer

switch (tsk.value(task)) {
  case 1:

    if (virDomainGetState( m_domain.m_dom,&state,&reason,0) < 0) {//check the domain state
        fprintf(stderr, "Cannot check guest state");
        break;
      }

    if (state==3){//if domain is suspended resume the domain
        if(virDomainResume(m_domain.m_dom)<0)
          break;
      }
    else if(virDomainCreate(m_domain.m_dom)<0)//if domain is not paused or not created
      break;
    qDebug()<<"\n state:"<<state<<"\nstart "<<index;
    ret="ok";
    break;

  case 2:
    qDebug()<<"\npause "<<index;
    if (virDomainGetState( m_domain.m_dom,&state,&reason,0) < 0) {//check the domain state
        fprintf(stderr, "Cannot check guest state");
        break;
      }
    if (state == VIR_DOMAIN_SHUTDOWN) {//if the domain is shutdown no need to pause
        fprintf(stderr, "Not saving guest that isn't running");
        break;
      }

    if (virDomainSuspend(dom) < 0) {//suspend the domain
        fprintf(stderr, "Unable to suspend guest");
        break;
      }

    fprintf(stderr, "Guest state suspended");
    ret= "ok";
    break;

  case 3:
    if(virDomainShutdown(m_domain.m_dom)<0)//shutdown the domain
      break;
    qDebug()<<"\nShutdown "<<index;
    ret="ok";
    break;

  case 4:
    if (virDomainGetState( m_domain.m_dom,&state,&reason,0) < 0) {//get the state of the domain
        fprintf(stderr, "Cannot check guest state");
        break;
      }
    if(state==VIR_DOMAIN_NOSTATE)
      ret="nostate";
    else if (state==VIR_DOMAIN_RUNNING)
      ret="started";
    else if(state==VIR_DOMAIN_PAUSED)
      ret="paused";
    else if (state==VIR_DOMAIN_SHUTDOWN)
      ret="stopped";
    else
      ret="";
  break;
  case 5:
    qDebug()<<virDomainGetXMLDesc(m_domain.m_dom,4);
    break;

  default:
    ret="nil";
    break;
  }

return ret;
}
