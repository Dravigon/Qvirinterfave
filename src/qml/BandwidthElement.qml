import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Rectangle{
    id:bandwidth

    Column{
        id:col_for
        spacing: 30
        Rectangle{
            id:inbound
            width: bandwidth.width
            height:bandwidth.height/8

            Column{

                Text {
                    id: inbound_text
                    text: qsTr("Inbound")
                    font.pixelSize: 20
                }
            Row{
                spacing: 5
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter
                    width: bandwidth.width/3
                    height: bandwidth.height/8
                    Row{
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 5
                        id: inbound_bandwidth_name
                        Text {
                            id: inbound_bandwidth_average
                            text: qsTr("Average")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: inbound_bandwidth_average_text
                            text: bandwidthInboundAverage
                        }
                    }
                }
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter

                    width: bandwidth.width/3
                    height: bandwidth.height/8
                    Row{
                                            anchors.verticalCenter: parent.verticalCenter
                        spacing: 5
                        id: inbound_bandwidth_peak
                        Text {
                            id: inbound_bandwidth_peak_tag
                            text: qsTr("Peak")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: inbound_bandwidth_peak_text
                            text: bandwidthInboundPeak
                        }
                    }
                }
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter

                    width: bandwidth.width/3
                    height: bandwidth.height/8
                    Row{
                                            anchors.verticalCenter: parent.verticalCenter
                        spacing: 5
                        id: inbound_bandwidth_burst
                        Text {
                            id: inbound_bandwidth_burst_id
                            text: qsTr("Burst")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: inbound_bandwidth_burst_text
                            text: bandwidthInboundBurst
                        }
                    }
                }
            }
        }
        }
        Rectangle{
            id:outbound
            width: bandwidth.width
            height:bandwidth.height/8

            Column{

                Text {
                    id: outbound_text
                    text: qsTr("Outbound")
                    font.pixelSize: 20
                }
            Row{
                spacing: 5
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter
                    width: bandwidth.width/3
                    height: bandwidth.height/8
                    Row{
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 5
                        id: outbound_bandwidth_name
                        Text {
                            id: outbound_bandwidth_average
                            text: qsTr("Average")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: outbound_bandwidth_average_text
                            text: bandwidthOutboundAverage
                        }
                    }
                }
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter

                    width: bandwidth.width/3
                    height: bandwidth.height/8
                    Row{
                                            anchors.verticalCenter: parent.verticalCenter
                        spacing: 5
                        id: outbound_bandwidth_peak
                        Text {
                            id: outbound_bandwidth_peak_tag
                            text: qsTr("Peak")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: outbound_bandwidth_peak_text
                            text: bandwidthOutboundPeak
                        }
                    }
                }
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter

                    width: bandwidth.width/3
                    height: bandwidth.height/8
                    Row{
                                            anchors.verticalCenter: parent.verticalCenter
                        spacing: 5
                        id: outbound_bandwidth_burst
                        Text {
                            id: outbound_bandwidth_burst_id
                            text: qsTr("Burst")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: outbound_bandwidth_burst_text
                            text: bandwidthOutboundBurst
                        }
                    }
                }
            }
        }
        }
    }
}

