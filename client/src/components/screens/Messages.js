import React from 'react';
import SearchBar from 'material-ui-search-bar';
import { Link } from 'react-router-dom';
import { ThemeProvider, ChatList, ChatListItem, Avatar, Column, Row, Title, Subtitle } from '@livechat/ui-kit';

import './Messages.css';

var test = "JA FÖR FAN";

class ChatsContent extends React.Component {
  state = {
    posts: [],
    otherID : null
  }

  componentDidMount(){
    this.getChats();
  }

  getChats = _ => {
    fetch('/api/chats')
      .then(response => response.json())
      .then(response => this.setState({ posts:response.data }))
      .catch(err => console.error(err))
  }

  handleChange = event => {
    alert("hejsa");
  this.setState({
    otherID: event.target.value
  });

  module.exports = { a: 'b' };
  alert("sdjkf");
  }


  render() {
    //this.state.otherID = 2;
    const chats = this.state.posts.map((item, i) => (

        <ThemeProvider>
				<ChatList className='chatlist'>
				  <Link to='/chat' className='router_link'>
				  	<ChatListItem className='chatlist_item' onClick={this.handleChange}>
					    <Avatar className='avatar' imgUrl='https://media.licdn.com/dms/image/C4E03AQFdhqSSucWLTg/profile-displayphoto-shrink_800_800/0?e=1550102400&v=beta&t=dsJgTRO-OBZ1GzdaZH7cv9XKqsczC0UJV5KK_PhXtFI' />
					    <Column className='message_content'>
					      <Row justify>

					        <Title ellipsis>{item.title}</Title>

					        <Subtitle nowrap>{item.createdDate.substring(0, 10) + " " + item.createdDate.substring(11, 16)}</Subtitle>
					      </Row>

					      <Subtitle ellipsis>
					        {'Hello, I also love DevOps, though not many friends of mine are doing the same.'}
					      </Subtitle>
					    </Column>
				  	</ChatListItem>
            </Link>
  				</ChatList>
			</ThemeProvider>
    ));
    //<TextInput onChangeText= {message => this.setState({message})}/>
    //<SendButton onClick={() => this.cardClick(i)} fit>
    return (
      chats
    );

  }

}

class ChatsScreen extends React.Component{

  render() {
    return (
      <div className='phone'>
        <div className='phone__header'>
            <SearchBar
              onChange={() => console.log('onChange')}
              onRequestSearch={() => console.log('onRequestSearch')}
              style={{
                backgroundColor: 'rgba(255,255,255,0.3)',
                width: '100%',
                height: '60%',
                margin: '0 1em',
                boxShadow: 'none',
                borderRadius: '30px',
              }}
            />
          </div>

        <div className='phone-content__wrapper'>
          <ChatsContent />
        </div>
      </div>
    );
  }
}

export default ChatsScreen;
