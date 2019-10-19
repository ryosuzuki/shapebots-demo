const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const usbs = [
'/dev/cu.usbserial-1410',
// '/dev/cu.usbserial-14140'
]
const ips = [
'10.201.31.187',
// '10.201.31.186'
]

for (let i = 0; i < usbs.length; i++) {
  let usb = usbs[i]
  const port = new SerialPort(usb, { baudRate: 9600 })
  const parser = new Readline()
  port.pipe(parser)

  parser.on('data', (line) => {
    console.log(`> ${line}`)
    let ip = ips[i]
    let command = line
    sendCommand(ip, command)
  })

}

const sendCommand = function(ip, command) {
  const dgram = require('dgram')
  const client = dgram.createSocket('udp4')
  let message = Buffer.from(command)
  let port = 893
  client.send(message, 0, message.length, port, ip, function(err, bytes) {
    if (err) throw err
    client.close()
  })
}



// port.write('ROBOT POWER ON\n')