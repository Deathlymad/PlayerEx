// Create a socket instance
			var socket = new WebSocket('ws://localhost:9999');
			
			function writeCSS(code)
			{
				var node = document.createElement('style');
				node.innerHTML = code;
				document.body.appendChild(node);
			}
			
			socket.onmessage = function(event) {
					var message = event.data;
					if (message[0] == 'c')
					{
						writeCSS(message.substring(1));
					}
					else if (message[0] == 'f')
					{
						//a file binary will follow
					}
			};
			socket.onopen = function(event) {
				socket.send("reload");
			};