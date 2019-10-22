const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const usbs = [
'/dev/cu.usbserial-14220',
'/dev/cu.usbserial-14230',
'/dev/cu.usbserial-14240'
]
const ips = [
'10.0.1.10',
'10.0.1.6',
'10.0.1.11',
// '10.201.31.186'
]

let prevs = [
'111111',
'111111',
'111111'
]


for (let i = 0; i < usbs.length; i++) {
  let usb = usbs[i]
  const port = new SerialPort(usb, { baudRate: 9600 })
  const parser = new Readline()
  port.pipe(parser)

  parser.on('data', (line) => {
    let ip = ips[i]
    let prev = prevs[i]
    let command = line
    if (command !== prev) {
      sendCommand(ip, command)
      prevs[i] = command
      console.log(command)
    }
  })

}

const sendCommand = function(ip, command) {
  const dgram = require('dgram')
  const client = dgram.createSocket('udp4')
  let message = Buffer.from(command)
  let port = 893
  if (ip !== '') {
    client.send(message, 0, message.length, port, ip, function(err, bytes) {
      if (err) throw err
      client.close()
    })
  }
}



// port.write('ROBOT POWER ON\n')