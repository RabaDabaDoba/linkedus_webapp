import React from 'react';
import SearchBar from 'material-ui-search-bar';
import { Link } from 'react-router-dom';
import { ThemeProvider, ChatList, ChatListItem, Avatar, Column, Row, Title, Subtitle } from '@livechat/ui-kit';

import './Messages.css';


class MessagesScreen extends React.Component {

  state = {
    test: []
  }
  componentDidMount(){
    this.getTest();
  }

  getTest = _ => {
    fetch('/api/test')
      .then(response => response.json())
      .then(response => this.setState({ posts:response.data }))
      .catch(err => console.error(err))
  }

  render() {
    const message = this.state.posts.map((item, i) => (
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
          <div className='card-content__line--sub'>{item.title}</div>
        <ThemeProvider>
				<ChatList className='chatlist'>
				  <Link to='/chat' className='router_link'>
				  	<ChatListItem className='chatlist_item'>
					    <Avatar className='avatar' imgUrl='https://media.licdn.com/dms/image/C4E03AQFdhqSSucWLTg/profile-displayphoto-shrink_800_800/0?e=1550102400&v=beta&t=dsJgTRO-OBZ1GzdaZH7cv9XKqsczC0UJV5KK_PhXtFI' />
					    <Column className='message_content'>
					      <Row justify>
                  /*The title should be the name of the other person*/
					        <Title ellipsis>{'Weiqing'}</Title>
                  /*this time should be tanken from the database*/
					        <Subtitle nowrap>{'14:31 PM'}</Subtitle>
					      </Row>
                /* This string should be the most recent message in the chatä*/
					      <Subtitle ellipsis>
					        {'Hello, I also love DevOps, though not many friends of mine are doing the same.'}
					      </Subtitle>
					    </Column>
				  	</ChatListItem>

            /*End of*/

            </Link>
  				</ChatList>
			</ThemeProvider>
    	</div>
    ));

    return (
      message
    );

  }

}


export default MessagesScreen;
